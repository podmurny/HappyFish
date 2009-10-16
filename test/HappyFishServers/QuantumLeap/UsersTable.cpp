#include "UsersTable.h"

CUsersTable::CUsersTable()
    :maxSockNum(100)
{
    head = NULL;
}

CUsersTable::~CUsersTable()
{
  ptr t;
  while(head != NULL)
    {
      t = head->next;
      delete head;
      head = t;
    }
}

void CUsersTable::AddRecord(string name, int sock_n)
{
    ClientInfo item;
    item.name = name;
    item.sock_n = sock_n;
    head = new node(item, head);
}

void CUsersTable::DeleteRecord(int sock_n)
{
    if(head == NULL)
    {
      return;
    }
    ptr t = head;
    ptr p;
    while(t->item.sock_n != sock_n)
    {
      p = t;
      t = t->next;
      if(t == NULL)
        break;
    }
    if(t == NULL)
    {
      return;
    }
    if(t == head)
        head = head->next;
    else
        p->next = t->next;
    delete t;
}

int CUsersTable::GetSock(string name)
{
    if(head == NULL)
      return -1;

    ptr t;
    for(t = head; t != NULL; t = t->next)
        if(t->item.name == name)
            return t->item.sock_n;
    return -1;
}

string CUsersTable::GetName(int sock)
{
    if(head == NULL)
        return "NOSOCK";

    ptr t;
    for(t = head; t != NULL; t = t->next)
        if(t->item.sock_n == sock)
            return t->item.name;

    return "NOSOCK";
}

ClientInfo* CUsersTable::GetInfoBySocket(int sock_n)
{
    if(head == NULL)
        return NULL;

    ptr t;
    for(t = head; t != NULL; t = t->next)
        if(t->item.sock_n == sock_n)
            return &(t->item);

    return NULL;
}

ClientInfo* CUsersTable::GetInfoByName(string name)
{
    if(head == NULL)
        return NULL;

    ptr t;
    for(t = head; t != NULL; t = t->next)
        if(t->item.name == name)
            return &(t->item);

    return NULL;
}

int CUsersTable::GetMaxSockNum()
{
    return this->maxSockNum;
}

void CUsersTable::SocketsToSet(fd_set& readset)
{
    ptr listIter;
    for(listIter = head; listIter != NULL; listIter = listIter->next)
    {
      FD_SET(listIter->item.sock_n, &readset);
    }
}