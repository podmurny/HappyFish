#include "NetworkClient.h"
#include <stdlib.h>
#include <iostream>
//для того что б запустить этот пример, вначале запустите MultiServer!
using namespace std; 
int main()
{
  //пример использования NetwprkClient
  NetworkClient client;
  client.ConnectToServer(6000, "localhost");
  if(client.GetValid() == DISCONNECT)
    {
      cout<<"Connect error"<<endl;
      exit(1);
    }
  client.SendMsg("eeeeeee");
  string str = "";
  client.WaitMsg(str);
  cout<<"String - "<<str<<endl;
  client.Disconnect();
  return 0;
}
