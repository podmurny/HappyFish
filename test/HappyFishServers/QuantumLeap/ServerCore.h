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

using namespace std;

#define CONNECT 1
#define DISCONNECT 0

#define ACTION_CLIENT_LOGIN 1
#define ACTION_CLIENT_TEXT 2

#define MAX_QUANTUM_SIZE 1024

struct Quantum
{
    short int eventID;
    int size;
    char eventBuff[1024];
};

class CServerCore
{
private:
    int listenSocket;            //Слушающий сокет
    sockaddr_in serverAddr;      //Локальный адрес сокета
    int maxSocketNumber;         //Максимальный номер сокета!!! Подумать над этим!!!
    int valid;                   //Состояния сервера
    CSocketTable userList;       //Список пользователей
    int serverPort;              //Порт который слушает сервер
    Quantum quantumBuf;          //все клиенты использують общий буфер (экономим память:))
private:
    bool BufferValid();
    void CloseConnection(int sockNum);
    void AddEvent();
public:
    CServerCore();
    ~CServerCore();
    int Init(int port);
    int Start();
    class CEventQueue;
    friend class CEventQueue;
};

class CServerCore::CEventQueue
{
private:
    struct node
    {
        Quantum Item;
        node* next;
        node* prev;
        node(Quantum data)
        {
            Item.eventID = data.eventID;
            Item.size = data.size;
            memcpy(Item.eventBuff,data.eventBuff,1024);
            next=0;
            prev=0;
        }
    };
private:
    node* current;
    CServerCore &server;
private:
    int HandleText();
    void DeleteEvent();
public:
    void AddEvent(Quantum event);
    void HandleEvent();
    bool IsEmpty();
    CEventQueue(CServerCore &serverLink);
    ~CEventQueue();
};

#endif	/* _SERVERCORE_H */

