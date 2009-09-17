//Unix includs
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
//My includs
#include "libsock.h"
#include "CTable.h"
//stl includs
#include <iostream>
#include <algorithm>
#include <set>
#include <string>
#include <sstream>
using namespace std;

char buf[1024];
int bytes_read;
set<int> clients;

int get_id_mes(char* id, char* mes, char* idmes)
{
  char *s = idmes;
  while(*s != '*')
    {
      if(*s == '\0')
	return -1;
      s++;
    }
  *s = '\0';
  id = idmes;
  s++;
  mes = s;
  string str(id);
  
  cout<<"We have "<<str<<" ------- "<<mes<<endl;
  return atoi(str.data());
}

void action(int sockfd)
{
  bzero(buf,sizeof(buf));
  bytes_read = recv(sockfd, buf, 1024, 0);
  if(bytes_read <= 0)
    {
      // Соединение разорвано, удаляем сокет из множества
      close(sockfd);
      clients.erase(sockfd);
    }
  else
    {
      cout<<"Message from "<<sockfd<<" : "<<buf<<endl;
      char* id;
      char* mes;
      get_id_mes(id, mes, buf);
      char a[3];
      int i = 0;
      int sendfd = get_id_mes(id, mes, buf);
      cout<<"Your socket id:"<<sendfd<<endl;
      //if(send(sendfd, mes, strlen(mes), 0) < 0)
      //return;
    }
}

int main()
{

  const char *as = "5";
  int a = atoi(as);
  cout<<"Server strt ok "<<a<<endl;
  int lsock, sock;
  struct sockaddr_in addr;
  
  lsock = socket(AF_INET, SOCK_STREAM, 0);
  if(lsock <= 0){
    perror("Listen Socket");
    exit(1);
  }
  fcntl(lsock, F_SETFL, O_NONBLOCK);

  if(Bind(addr, lsock, "any", 4000) < 0){
    perror("Bind");
    exit(1);
  }
  if(Listen(lsock) < 0){
    perror("Listen");
    exit(1);
  }
  
  clients.clear();
  
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
	    action(*it);
	}
    //end of while
    }
  return 0;
}
