#include "ActionQueue.h"

CActionQueue::CActionQueue()
{
    head=0;
    tail=0;
};

CActionQueue::~CActionQueue()
{
    while (!IsEmpty())
    {
        node* t=head;
        head=t->next;
        delete t;
    };
};

Quantum CActionQueue::Get()
{
    Quantum v;
    v.eventID= head->Item.eventID;
    v.size = head->Item.size;
    v.eventBuff = head->Item.eventBuff;
    node* t=head->next;
    delete head;
    head=t;
    return v;
};

void CActionQueue::Put(Quantum x)
{
    node* t=tail;
    tail=new node(x);
    if (head==0) head=tail;
    else t->next=tail;
};

int CActionQueue::IsEmpty()
{
    return head==0;
};
