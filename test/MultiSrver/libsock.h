#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<cstring>
#include<stdio.h>
#define NOT_ACTIV_CONN_COUNT 5
#define FOREVER for(;;)

int create_addr(struct sockaddr_in&  addr, const char* ipstr, const short int port)
{
  bzero(&addr,sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  if(strcmp(ipstr,"localhost") == 0)
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  else
    if((strcmp(ipstr,"any") == 0) || !ipstr)
      addr.sin_addr.s_addr = htonl(INADDR_ANY);
    else
      if(inet_aton(ipstr,&addr.sin_addr) == 0)
	{
	  bzero(&addr,sizeof(addr));
	  return -1;
	} 
  return sizeof(addr);
}

int Bind(struct sockaddr_in& addr, int sock_fd, const char* ipstr = NULL, const short int port = -1)
{
  if((ipstr != NULL) && (port >= 0))
    if(create_addr(addr, ipstr, port) < 0)
      return -1;
  if(bind(sock_fd,(struct sockaddr*)&addr,sizeof(addr)) < 0)
    return -1;
  return 0;
}

int Listen(int& sock_fd)
{
  if(listen(sock_fd,NOT_ACTIV_CONN_COUNT) < 0)
    return -1;
  return 0;
}

int Connect(struct sockaddr_in& addr, int sock_fd, const char* ipstr = NULL, const short int port = -1)
{
  if((ipstr != NULL) && (port >= 0))
    if(create_addr(addr, ipstr, port) < 0)
      return -1;
  if(connect(sock_fd,(struct sockaddr*)&addr,sizeof(addr)) < 0)
    return -1;
  return 0;
}
