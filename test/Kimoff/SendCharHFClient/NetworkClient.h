#ifndef network
#define network
#include "gsg_socket.h"
#include <unistd.h>
#include <string>
//using std::string;
/*
  Это первый класс, написаный ориентируясь на диаграмму классов,
  созданную в начале лета.
*/

#define CONNECT 1
#define DISCONNECT 0

class NetworkClient
{
 private:
  int client_sock_fd;
  sockaddr_in server_addr;
  int valid;
 private:
  void SetValid(int v);
 public:
  NetworkClient();
  ~NetworkClient();
  void ConnectToServer(int port, const char* ipstr);
  void Disconnect();
  int LoginToServer(char* pass, char* login);
  int SendMsg(std::string msg);
  int WaitMsg(char* buffer, int size);
  int GetValid() const {return valid;}
};

#endif
