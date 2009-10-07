#include<unistd.h>
#include<pthread.h>
#include<iostream>
#include<cstdio>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sstream>
using namespace std;

const int CLIENTS_QUEUE=5;	//Max available queue of clients to wait for connection to server

struct ClientData	//Structure that contains all client data
{
	int sock;		//Socket id
	char buf[1024];		//Buffer for the message
    	int bytes_read;		//Size of the received message
	pthread_t thr;	//Thread id
};

ClientData clients[30];	//Clients array (in perspective - dynamic list)

int from_str_to_int(string &str)//у меня не работал atoi хз почему...
{                              //написал её аналог только работая со string, а не с char*
  int v = 0;
  stringstream in;
  in << str;
  in >> v;
  return v;
}
/*Оптимизировать это гавно!!!*/
int get_id_mes(char* idmes)  //разделяем строку с получиным сообщением
                                                  //на id и сообщение
{
  char *s = idmes;
  
  //разделяем строку на две части: id - строка кому отправлять
  while(*s != '*')
    {
      if(*s == '\0')
	return -1;//неправильный формат строки
      s++;
    }
  *s = '\0';

  string str(idmes);
  /*
    здесь у нас есть строка с именем пользователя, которому адрисовано сообщение
    по этой строке надо найти индетификатор сокета, в который мы будем писать сообщение
    !!!Но пока имя пользователя - это индетификатор сокета, определённый сервером!!!
    современем я это доделаю)
    Здесь так же можем использовать базу данных
     */
  int a = from_str_to_int(str);//в а сохраняем индитефикатор сокета
  
  //заново склеиваем строку
  s = idmes;
  while(*s != '\0')
    {
      s++;
    }
  *s = '*';
  //возвращаем индификатор сокета куда отправлять сообщение
  return a;//
}

void* process_client(void* client_data)
{
	ClientData* clientPtr = (ClientData*)client_data;	//Convert void* to ClientData*
	ClientData& client = *clientPtr;			//Get data into ClientData variable by reference
	int ss = 0;
	//ClientData& client = *(ClientData*)client_data;		//Probably other way to do the same
	cout<<"Your sockID: "<<client.sock<<endl;;
	while(1)	//Inner cycle to process client
	{
            	client.bytes_read = recv(client.sock, client.buf, 1024, 0);	//Receive message
		if (client.buf == "quit") break;		//Cycle ending condition
		if(client.bytes_read > 0) 		//Print received message only once
		{
			cout << endl << "Buffer: " << client.buf << endl;		//Output received message
			ss = get_id_mes(client.buf);
			if(ss > 0)
			  for(int i = 0; i < 30; i++)
			    if(clients[i].sock == ss){
			      send(ss, client.buf, client.bytes_read, 0);	//Send message back (this is an echo server
			      break;
			    }
		}
		else break;
	}
    
       	 close(client.sock);	//Close socket	
}

int main()
{

	int listener;	//Socket to apply clients
	struct sockaddr_in addr;	//Adress to connect listener socket
	int clients_quan = 0;	//Number of clients online
	
	pthread_t thrID;

	listener = socket(AF_INET, SOCK_STREAM, 0);	//Create listener socket on the server
    
	//Listener parameters
   	addr.sin_family = AF_INET;		
    	addr.sin_port = htons(6000);			//Port for all the clients to connect on this server
    	addr.sin_addr.s_addr = htonl(INADDR_ANY);
    	bind(listener, (struct sockaddr *)&addr, sizeof(addr));		//Bind listener socket to the port

    	listen(listener, CLIENTS_QUEUE);	//Initiate listening

	while(1)	//Neverending cycle
	{
		clients[++clients_quan].sock = accept(listener, NULL, NULL);	//Accept client
		//Here we create a new thread
		pthread_create(&clients[clients_quan].thr,0,&process_client,(void*)&clients[clients_quan]); //Client is processed in this thread		
		//After finishing this iteration listener keeps waiting for a new client, while new-made thread is active
	}

	return 0;
}
