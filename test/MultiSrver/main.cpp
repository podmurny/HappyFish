//Unix includs
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
//My includs
#include "libsock.h"
#include "CTable.h"
#include "../Podmurny_Vyacheslav/CClient/CClient.h"
//stl includs
#include <iostream>
#include <algorithm>
#include <set>
#include <string>
#include <sstream>
using namespace std;

char buf[1024];//все клиенты использують общий буфер (экономим память:))
int bytes_read;//необходимо занть сколько мы прочитали символов с потока
set<int> clients;//множество клиентов

int from_str_to_int(string &str)//у меня не работал atoi хз почему...
{                              //написал её аналог только работая со string, а не с char*
  int v = 0;
  stringstream in;
  in << str;
  in >> v;
  return v;
}
string from_int_to_string(int input)
{
	string result;
	stringstream out;
	out << input;
	result = out.str();
	return result;
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

int action(int sockfd)   //функция которая обрабатывает запрос клиента
//может эту функцию стоит назвать routing?
{
  bzero(buf,sizeof(buf));
  bytes_read = recv(sockfd, buf, 1024, 0);
  //При закрытии соединения на сотороне клиента, сокет на стороне сервера будет активным
  //Но мы несможем с него читать данные, таким образом мы можем провверять когда клиет отключится
  CClient client;
  if(bytes_read <= 0)

    {
      // Соединение разорвано, удаляем сокет из множества
      cout<<"Connection #"<<sockfd<<" close"<<endl;
	  string sockfd_to_string = from_int_to_string(sockfd);
	  string message = "Connection #" + sockfd_to_string + " close";

	  client.write_log_to_file(message);
      close(sockfd);
      clients.erase(sockfd);
    }
  else
    {
      cout<<"Message from "<<sockfd<<" : "<<buf<<endl;
      int sendfd = get_id_mes(buf);//в соответствии с полученной строкой определить номер сокета куда будем дальше писать сообщение
      if(sendfd < 0)
	return -1;
      cout<<"Your socket id:"<<sendfd<<endl;
      //дальше мы должны что то  комуто отправлять
      if(send(sendfd, buf, 1024, 0) < 0)
	return -1;
    }
  return 0;
}

int main()
{

  int lsock, sock;
  struct sockaddr_in addr;
  
  lsock = socket(AF_INET, SOCK_STREAM, 0);
  if(lsock <= 0){
    perror("Listen Socket");
    exit(1);
  }
  fcntl(lsock, F_SETFL, O_NONBLOCK);

  if(Bind(addr, lsock, "any", 6000) < 0){
    perror("Bind");
    exit(1);
  }
  if(Listen(lsock) < 0){
    perror("Listen");
    exit(1);
  }
  
  clients.clear();
  
  cout<<"Server start: OK"<<endl;

  while(1)
    {
      fd_set readset;
      FD_ZERO(&readset);
    
      FD_SET(lsock, &readset);  
      for(set<int>::iterator it = clients.begin(); it != clients.end(); it++)
	FD_SET(*it, &readset);
      
      timeval timeout;
      timeout.tv_sec = 15;
      timeout.tv_usec = 0;
      int mx = max(lsock, *max_element(clients.begin(), clients.end()));
      
      if(select(mx+1, &readset, NULL, NULL, &timeout) <= 0)
	{
	  continue;
	}
      
      //Провкрка всех сокетов
      if(FD_ISSET(lsock,&readset))
	{
	  // Поступил новый запрос на соединение, используем accept
	  cout<<"New connection"<<endl;
	  int sock = accept(lsock, NULL, NULL);
	  if(sock < 0)
	    {
	      perror("accept");
	      exit(3);
	    }    
	  cout<<"User number: "<<sock<<endl;
	  fcntl(sock, F_SETFL, O_NONBLOCK);
	  clients.insert(sock);
	}
      for(set<int>::iterator it = clients.begin(); it != clients.end(); it++)
        {
	  if(FD_ISSET(*it, &readset))
	    if(action(*it) < 0)
	      cout<<"invalid routing"<<endl;
	}
    //end of while
    }
  return 0;
}
