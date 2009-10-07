#include <unistd.h>
#include <pthread.h>
#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <cstring>
#include <sstream>
//#include<arpa/inet.h>
//#include <fcntl.h>
//#include <string>

using namespace std;

const int CLIENTS_QUEUE = 5;	//Max available queue of clients to wait for connection to server
const int BUFFER_SIZE = 1024;
const int CLIENTS_QUANTITY = 30;

struct ClientData	//Structure that contains all client data
{
	int sock;		//Socket id
	char buf[BUFFER_SIZE];		//Buffer for the message
    	int bytes_read;		//Size of the received message
	pthread_t thr;		//Thread id
	

	ClientData()		//Constructor by default
	{
		bzero(buf,sizeof(buf));
		bytes_read = 0;
	}
};

ClientData clients[CLIENTS_QUANTITY];	//Clients array (in perspective - dynamic list)

void copy_buffer(char* FROM, char* TO)	//Copy one buffer's data to another
{
	for (int i=0;i<BUFFER_SIZE;i++)
	{
		TO[i] = FROM[i];
	}
}

int from_str_to_int(string &str)	//Convert string to int
{                             
  int v = 0;
  stringstream in;
  in << str;
  in >> v;
  return v;
}

int get_receiver_id(char* idmes)  //Separate string, sent by client, to receiver id and the message itself (separator symbol is "*")
{
  char *s = idmes;	//String to process ("s" is)
  
  while(*s != '*')	//Separate string into two (find "*" and replace it with "\0")
    {
      if(*s == '\0')
	return -1;	//Haven't found "*" - wrong string format
      s++;		//Increase pointer (go to the next string symbol)
    }
  *s = '\0';		//Separate id from the message in string

  string str(idmes);	//Get id into new string

//So far we use only socket id, but in perspective it will be client's login and work with the database

  int a = from_str_to_int(str);		//Save socket id
  
  //Restore the string (replace back "\0" in the middle of the received string to "*")
  s = idmes;
  while(*s != '\0')
    {
      s++;
    }
  *s = '*';

  return a;	//Return receiver socket id
}

/* Each cycle in every client's thread there is made a check - if there is a new message FROM this client. If there is a message receiver by current client's thread - we check if receiver's adress is entered correctly in this message, and then send it to the receiver
*/
void* process_client(void* current_client)
{
	int* intPtr = (int*)current_client;	//Convert void* to int*
	int current = *intPtr;	//Get data into int variable

	cout<<""<<endl;	
	while(1)	//Inner cycle to process client
	{
		bzero(clients[current].buf,sizeof(clients[current].buf));		//Clear the buffer
	     	clients[current].bytes_read = recv(clients[current].sock, clients[current].buf, BUFFER_SIZE, 0); //Receive message (non-blocking receive)
		cout << clients[current].buf;
		//cout << clients[current].bytes_read;			
		//cout << clients[current].bytes_read << endl;		
		if (clients[current].buf == "quit") break;		//Cycle ending condition
		if (clients[current].bytes_read <= 0) break;		//If client has broken communication (client socket is closed) - close server socket
		
		if(clients[current].bytes_read > 0) 		//If there is a message received
		{
			int receiver = get_receiver_id(clients[current].buf);		//Get receiver client id
			for (int i=1; i<=CLIENTS_QUANTITY; i++)				//Check if receiver's id is entered correct in the message
				if (receiver == i)
					send(clients[receiver].sock, clients[current].buf, clients[current].bytes_read, 0);	//Send message to receiver
			
			//cout << endl << "Buffer: " << clients[current].buf << endl;		//Output received message
			//cout << clients[current].buf;		//Output received character
			if (clients[current].buf == "ENTER") cout << endl;
		}
	}

	 cout << current << " closed." << endl; 
       	 close(clients[current].sock);	//Close socket	
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

		clients[++clients_quan].sock = accept(listener, NULL, NULL);	//Accept new client
		cout<<"Client "<<clients_quan<<" connected. It's socket id is: "<<clients[clients_quan].sock<<endl;
		//Here we create a new thread
		pthread_create(&clients[clients_quan].thr,0,&process_client,(void*)&clients_quan);	//Client is processed in this thread		
		//After finishing this iteration listener keeps waiting for a new client, while new-made thread is active
	}

	return 0;
}
