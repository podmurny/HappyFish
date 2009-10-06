#ifndef SOTABLE
#define SOTABLE

#include <stdlib.h>
#include <pthread.h>
#include <string>
using std::string;

struct Item
{
  string name;
  int sock_n;
};

struct node
{
  Item item;
  node* next;
  node(Item i, node* x)
    :item(i), next(x){}
};

typedef node* ptr;

class CSocketTable
{
private:
  ptr head;
  pthread_mutex_t lockx;
public:
  CSocketTable();
  ~CSocketTable();
  void AddRecord(string name, int sock_n);
  void DeleteRecord(int sock_n);
  int GetSock(string name);
  ptr GetHead();
  string GetName(int sock);
  void ChangeName(int sock, string name);
};

#endif
