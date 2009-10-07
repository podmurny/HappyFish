#include "ServerCore.h"

CServerCore::CEventQueue::CEventQueue(CServerCore &serverLink)
    :server(serverLink)
{
    current = 0;
}

CServerCore::CEventQueue::~CEventQueue()
{
    while (!IsEmpty())
    {
        DeleteEvent();
    }
}

void CServerCore::CEventQueue::AddEvent(Quantum event)
{
    node* t = new node(event);
    if (current == 0)
    {
        t->next = t;
        t->prev = t;
        current = t;
    }
    else
    {
        t->next = current;
        current->prev->next = t;

    }
}

void CServerCore::CEventQueue::DeleteEvent()
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

void CServerCore::CEventQueue::HandleEvent()
{
    if(IsEmpty())
        return;
    if(current->Item.eventID == ACTION_CLIENT_TEXT)
        if(HandleText() == 0)
        {
            current = current->next;
        }
        else
        {
            DeleteEvent();
        }
}

bool CServerCore::CEventQueue::IsEmpty()
{
    return current==0;
}

int CServerCore::CEventQueue::HandleText()
{
    return 0;
}