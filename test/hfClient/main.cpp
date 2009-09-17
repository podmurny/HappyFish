#include "libsock.h"
#include <iostream>
#include <string>
using namespace std;

struct Msg
{
  string Who;
  string mes;
};

int main()
{
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in addr;

  if(Connect(addr,sock,"any",4000) < 0)
    perror("localhost");
  switch(fork())
    {
    case (pid_t)-1:
      perror("fork");
      return 0;
      break;
    case (pid_t)0:
      FOREVER
	{
	  string buf;
	  cout<<"Enter msg: ";
	  cin>>buf;
	  send(sock,buf.data(), buf.length(), 0);
	}
      break;
    default:
      char buf[1024];
      int bytes_read;
      FOREVER
	{
	  bzero(buf,sizeof(buf));
	  bytes_read = recv(sock, buf, 1024, 0);
	  if(bytes_read >= 0)
	    {
	      cout<<endl<<"Message from server: "<<buf<<endl<<"Enter msg:";
	    }
	}
    }
  return 0;
}
