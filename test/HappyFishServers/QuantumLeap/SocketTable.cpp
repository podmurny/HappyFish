#include "SocketTable.h"

CSocketTable::CSocketTable()
{
  //CSocketTable tb;
  pthread_mutex_init(&lockx, 0);
  head = NULL;
}

CSocketTable::~CSocketTable()
{
  ptr t;
  while(head != NULL)
    {
      t = head->next;
      delete head;
      head = t;
    }
  pthread_mutex_unlock(&lockx);
}

void CSocketTable::AddRecord(string name, int sock_n)
{
  if(!pthread_mutex_lock(&lockx))
    {
      Item item;
      item.name = name;
      item.sock_n = sock_n;
      head = new node(item, head);
      pthread_mutex_unlock(&lockx);
    }
}

void CSocketTable::DeleteRecord(int sock_n)
{
  if(!pthread_mutex_lock(&lockx))
    {
      if(head == NULL)
	{
	  pthread_mutex_unlock(&lockx);
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
	  pthread_mutex_unlock(&lockx);
	  return;
	}
      if(t == head)
	head = head->next;
      else
	p->next = t->next;
      delete t;
      pthread_mutex_unlock(&lockx);
    }
}

int CSocketTable::GetSock(string name)
{
  if(!pthread_mutex_lock(&lockx))
    {
      if(head == NULL)
	{
	  pthread_mutex_unlock(&lockx);
	  return -1;
	}
      ptr t;
      for(t = head; t != NULL; t = t->next)
	if(t->item.name == name)
	  {
	    pthread_mutex_unlock(&lockx);
	    return t->item.sock_n;
	  }
      pthread_mutex_unlock(&lockx);
    }
  return -1;
}

string CSocketTable::GetName(int sock)
{
  if(!pthread_mutex_lock(&lockx))
    {
      if(head == NULL)
	{
	  pthread_mutex_unlock(&lockx);
	  return "NOSOCK";
	}
      ptr t;
      for(t = head; t != NULL; t = t->next)
	if(t->item.sock_n == sock)
	  {
	    pthread_mutex_unlock(&lockx);
	    return t->item.name;
	  }
      pthread_mutex_unlock(&lockx);
    }
  return "NOSOCK";
}

void CSocketTable::ChangeName(int sock, string name)
{
  if(!pthread_mutex_lock(&lockx))
    {
      if(head == NULL)
	{
	  pthread_mutex_unlock(&lockx);
	  return;
	}
      ptr t;
      for(t = head; t != NULL; t = t->next)
	if(t->item.sock_n == sock)
	  {
	    t->item.name = name;
	    pthread_mutex_unlock(&lockx);
	    return;
	  }
      pthread_mutex_unlock(&lockx);
    }
}

ptr CSocketTable::GetHead()
{
  return head;
}
