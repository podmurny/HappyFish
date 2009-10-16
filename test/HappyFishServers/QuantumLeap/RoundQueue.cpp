#include "RoundQueue.h"
//Это мне впадло коментить!!!
CRoundQueue::CRoundQueue()
{
    current = 0;
}

CRoundQueue::~CRoundQueue()
{
    while (!IsEmpty())
    {
        Delete();
    }
}

bool CRoundQueue::IsEmpty()
{
    return current == 0;
}

void CRoundQueue::Delete()
{
    if(IsEmpty())
        return;
    if(current->next == current)
    {
        delete current;
        current = 0;
    }
    else
    {
        node* t = current;
        current = current->next;
        current->prev = t->prev;
        t->prev->next = current;
        delete t;
    }
}

void CRoundQueue::Add(Item &data)
{
    node* t = new node(data);
    if (current == 0)
    {
        t->next = t;
        t->prev = t;
        current = t;
    }
    else
    {
        node* prev = current->prev;
        current->prev = t;
        t->next = current;
        prev->next = t;
        t->prev = prev;

    }
}

void CRoundQueue::Next()
{
    if(!IsEmpty())
        current = current->next;
}

Item* CRoundQueue::GetCurrentPointer()
{
    if(this->IsEmpty())
        return 0;
    Item* ptr = &(current->item);
    return ptr;
}
