#include "gsg_socket.h"

int create_addr(struct sockaddr_in&  addr, const char* ipstr, const short int port)
{
  bzero(&addr,0);
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
	  bzero(&addr,0);
	  return -1;
	}
  return sizeof(addr);
}

int Bind(struct sockaddr_in& addr, int sock_fd, const char* ipstr, const short int port)
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

int Connect(struct sockaddr_in& addr, int sock_fd, const char* ipstr, const short int port)
{
  if((ipstr != NULL) && (port >= 0))
    if(create_addr(addr, ipstr, port) < 0)
      return -1;
  if(connect(sock_fd,(struct sockaddr*)&addr,sizeof(addr)) < 0)
    return -1;
  return 0;
}

int LOH()
{
    return 0;
}
