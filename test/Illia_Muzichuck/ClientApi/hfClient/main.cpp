#include "NetworkClient.h"
#include <iostream>
using namespace std;

NetworkClient client;

int main()
{
  char msg[] = "4*Hello, server!";
  client.ConnectToServer(6000, "localhost");
  if(client.GetValid() == DISCONNECT)
    cout<<"ERROR"<<endl;
  else
    {
      client.SendMsg(msg, sizeof(msg));
      char buf[1024];
      client.WaitMsg(buf, 1024);
      cout<<"Buffer : "<<buf<<endl;
    }
  client.Disconnect();
  cout<<"hhhh"<<endl;
  return 0;
}
