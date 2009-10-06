#include "ServerCore.h"

CServerCore serv;

int main()
{
  if(serv.Init(6000) < 0)
    return 0;
  serv.Start();
  return 0;
}
