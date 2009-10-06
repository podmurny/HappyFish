/* 
 * File:   ServerCore.h
 * Author: otherside
 *
 * Created on October 5, 2009, 2:15 PM
 */

#ifndef _SERVERCORE_H
#define	_SERVERCORE_H

#include "SocketTable.h"
#include "gsg_socket.h"
#include <fcntl.h>
#include <iostream>
#include "ActionQueue.h"
using namespace std;

#define CONNECT 1
#define DISCONNECT 0

#define ACTION_CLIENT_LOGIN 1

#define MAX_QUANTUM_SIZE 1024

class CServerCore
{
private:
    int listenSocket;            //Слушающий сокет
    sockaddr_in serverAddr;      //Локальный адрес сокета
    int maxSocketNumber;         //Максимальный номер сокета!!! Подумать над этим!!!
    int valid;                   //Состояния сервера
    CSocketTable userList;       //Список пользователей
    int serverPort;              //Порт который слушает сервер
    char buf[MAX_QUANTUM_SIZE];              //все клиенты использують общий буфер (экономим память:))
public:
    CServerCore();
    ~CServerCore();
    int Init(int port);
    int Start();
};

#endif	/* _SERVERCORE_H */

