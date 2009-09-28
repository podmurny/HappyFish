#ifndef Socket
#define Socket
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<cstring>
#include<stdio.h>
#define NOT_ACTIV_CONN_COUNT 5
#define FOREVER for(;;)

int create_addr(struct sockaddr_in&  addr, const char* ipstr, const short int port);
int Bind(struct sockaddr_in& addr, int sock_fd, const char* ipstr = NULL, const short int port = -1);
int Listen(int& sock_fd);
int Connect(struct sockaddr_in& addr, int sock_fd, const char* ipstr = NULL, const short int port = -1);
int LOH();

#endif
