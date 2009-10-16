/* 
 * File:   ServerCore.h
 * Author: otherside
 *
 * Created on October 5, 2009, 2:15 PM
 */

#ifndef _SERVERCORE_H
#define	_SERVERCORE_H

#include "UsersTable.h"
#include "gsg_socket.h"
#include <fcntl.h>
#include <iostream>
#include <list>
#include "RoundQueue.h"
using namespace std;

#define CONNECT 1
#define DISCONNECT 0

#define ACTION_CLIENT_LOGIN 1
#define ACTION_CLIENT_TEXT 2

#define MAX_QUANTUM_SIZE 1024

class CServerCore
{
private:
    int listenSocket;            //Слушающий сокет
    sockaddr_in serverAddr;      //Локальный адрес сокета
    int valid;                   //Состояния сервера
    CUsersTable userList;       //Список пользователей
    int serverPort;              //Порт который слушает сервер
    char serverBuf[sizeof(Quantum)];//все клиенты использують общий буфер (экономим память:))
    fd_set readset;
    timeval timeout;

    fd_set bufset;
private:
    bool BufferValid();
    void CloseConnection(int sockNum);
    void FillReadSet();
    void NewConnection();
    void AddEvent(ClientInfo* clientPtr);
    void HandleCurrentEvent(ClientInfo* clientPtr);
    bool FillServerBufFromSocket(int sock);
public:
    CServerCore();
    ~CServerCore();
    int Init(int port);
    int Start();
};

#endif	/* _SERVERCORE_H */

