#include "ServerCore.h"

CServerCore::CServerCore() //исправить 100!!!
    :listenSocket(-1), valid(DISCONNECT), serverPort(0)
{
    bzero(&serverAddr,sizeof(serverAddr));
}

CServerCore::~CServerCore()
{
}

void CServerCore::AddEvent(ClientInfo* clientPtr)
{
}

void CServerCore::HandleCurrentEvent(ClientInfo* clientPtr)
{
}

bool CServerCore::BufferValid() //TODO: написать проверку структуры(буфера)
{
    return true;
}

void CServerCore::FillReadSet()
{
    FD_ZERO(&readset);
    FD_SET(listenSocket, &readset);
    userList.SocketsToSet(readset);
    timeout.tv_sec = 0;
    timeout.tv_usec = 10;
}

void CServerCore::NewConnection()
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

void CServerCore::CloseConnection(int sockNum)
{
     userList.DeleteRecord(sockNum);
     close(sockNum);
}

bool CServerCore::FillServerBufFromSocket(int sock)
{
     bzero(serverBuf, sizeof(Quantum));
     if(recv(sock, serverBuf, sizeof(Quantum), 0) <= 0)
     {
         bzero(serverBuf, sizeof(Quantum));
         return false;
     }
     if(!BufferValid())
     {
         bzero(serverBuf, sizeof(Quantum));
         return false;
     }
     return true;
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
    valid = CONNECT;
    return 0;
}

int CServerCore::Start()
{
    CUsersTable::Iterator listIter(userList);
    while(1)
    {
        FillReadSet();

        if(select(userList.GetMaxSockNum() + 1, &readset, NULL, NULL, &timeout) > 0)
        {
            if(FD_ISSET(listenSocket,&readset))	//Если ктото ломится к листенеру
                NewConnection();

            for(listIter.Begin(); !listIter.End(); listIter.Next())
            {

                if(FD_ISSET(listIter.itemPtr->sock_n, &readset))	//Если на порт данного сокета ктото ломится
                    if(!FillServerBufFromSocket(listIter.itemPtr->sock_n))
                        CloseConnection(listIter.itemPtr->sock_n);
                    else
                        AddEvent(listIter.itemPtr);

                if(listIter.itemPtr->rqPtr != NULL) //есди у этого клиента есть какието события
                    HandleCurrentEvent(listIter.itemPtr);
            }

        }//end of select

    }
    return 0;
}
