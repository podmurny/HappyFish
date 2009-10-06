#include "ServerCore.h"

CServerCore::CServerCore() //исправить 100!!!
    :listenSocket(-1), maxSocketNumber(100), valid(DISCONNECT), serverPort(0)
{
    bzero(&serverAddr,sizeof(serverAddr));
}

CServerCore::~CServerCore()
{
}

int CServerCore::Init(int port)
{
    serverPort = port;
    listenSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(listenSocket <= 0)
    {
      return -1;
    }
    fcntl(listenSocket, F_SETFL, O_NONBLOCK);

    if(Bind(serverAddr, listenSocket, "any", serverPort) < 0)
    {
      perror("Bind");
      return -1;
    }
    if(Listen(listenSocket) < 0)
    {
      return -1;
    }
    maxSocketNumber = listenSocket;
    valid = CONNECT;
    return 0;
}

int CServerCore::Start()
{
    CActionQueue queue;
    fd_set readset;
    ptr listIter;
    while(1)
    {
        FD_ZERO(&readset);
        FD_SET(listenSocket, &readset);
        for(listIter = userList.GetHead(); listIter != NULL; listIter = listIter->next)
        {
          FD_SET(listIter->item.sock_n, &readset);
        }
        timeval timeout;
        timeout.tv_sec = 0;
        timeout.tv_usec = 10;
        if(select(maxSocketNumber + 1, &readset, NULL, NULL, &timeout) <= 0)
        {
          //continue;
        }
        if(FD_ISSET(listenSocket,&readset))	//Если ктото ломится к листенеру
        {
          
            cout<<"New connection"<<endl;
            int sock = accept(listenSocket, NULL, NULL);
            if(sock < 0)
            {
                perror("accept");
            }
            cout<<"User number: "<<sock<<endl;
            fcntl(sock, F_SETFL, O_NONBLOCK);
            
            userList.AddRecord("NONE", sock);
        }
        for(listIter = userList.GetHead(); listIter != NULL; listIter = listIter->next)
        {
	  if(FD_ISSET(listIter->item.sock_n, &readset))	//Если на порт данного сокета ктото ломится
          {
              if(recv(listIter->item.sock_n, buf, MAX_QUANTUM_SIZE, 0) <= 0)
              {
                  userList.DeleteRecord(listIter->item.sock_n);
                  close(listIter->item.sock_n);
              }
              else
              {
                  //Quantum event;
                  //event.eventID = short(buf);
              }
          }
	}
    }
    return 0;
}
