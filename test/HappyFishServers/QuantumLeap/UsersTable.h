/* 
 * File:   UsersTable.h
 * Author: otherside
 *
 * Created on October 16, 2009, 7:49 PM
 */

#ifndef _USERSTABLE_H
#define	_USERSTABLE_H

#include <stdlib.h>
#include <string>
#include "RoundQueue.h"
#include "gsg_socket.h"
using std::string;

struct ClientInfo//структура с данными о клиенте
{
  string name;
  int sock_n;
  CRoundQueue *rqPtr;//указатель на очередь событий
  ClientInfo()
      :rqPtr(NULL){}//по умолчанию у клиента нет очереди событий
};

/*
 * Таблица пользователей
 * Возможности
 * 1)Добавить информацию о клинте(ClientInfo)
 * 2)Удалить её
 * 3)Найти номер сокета клиента, по имени клиента
 * 4)Найти имя клиента, по его сокету
 * 5)Вернуть указатель на иформацию о клиенте(ClientInfo), найденый по имени
 * 6)Вернуть указатель на иформацию о клиенте(ClientInfo), найденый по номеру сокета
 * 7)Узнать самый большой номер сокета
 * 8)Записать все сокеты клиентов в множество для последующего чтения функцией select
 */
class CUsersTable
{
private:

    struct node//Это зависит от реализации
    {
      ClientInfo item;
      node* next;
      node(ClientInfo i, node* x)
        :item(i), next(x){}
    };
    typedef node* ptr;

private:
   ptr head;
   int maxSockNum;
public:
   CUsersTable();
   ~CUsersTable();

   //У этого класа должен быть ИМЕННО ТАКОЙ ИНТЕРЕФЕЙСС
   void AddRecord(string name, int sock_n);
   void DeleteRecord(int sock_n);
   int GetSock(string name);
   string GetName(int sock);
   ClientInfo* GetInfoBySocket(int sock_n);
   ClientInfo* GetInfoByName(string name);
   int GetMaxSockNum();
   void SocketsToSet(fd_set& readset);

   class Iterator;
   friend class Iterator;
};


class CUsersTable::Iterator
{
private:
    CUsersTable &table;
    typedef CUsersTable::node* ptr;
    ptr current;

public:
     ClientInfo* itemPtr;

public:
    Iterator(CUsersTable &t)
    :table(t)
    {
        current = NULL;
        itemPtr = NULL;
    }

    ~Iterator()
    {
    }
    
    void Begin()
    {
        current = table.head;
        itemPtr = &(current->item);
    }

    bool End()
    {
        if(current == NULL)
            return true;
        return false;
    }

    void Next()
    {
        if(!End())
        {
            current = current->next;
            if(current != NULL)
                itemPtr = &(current->item);
            else
                itemPtr = NULL;
        }
    }
};

#endif	/* _USERSTABLE_H */

