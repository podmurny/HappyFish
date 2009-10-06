#include "ServerCore.h"
#include <stdlib.h>
#include <iostream>
using namespace std;
CServerCore server;

int main()
{
    if(server.Init(7777) == -1)
        exit(1);
    cout<<"SERVER START 0K"<<endl;
    return 0;
}
