/* 
 * File:   ActionQueue.h
 * Author: otherside
 *
 * Created on October 5, 2009, 4:08 PM
 */

#ifndef _ACTIONQUEUE_H
#define	_ACTIONQUEUE_H

struct Quantum
{
    short int eventID;
    int size;
    void* eventBuff;
};

class CActionQueue
{
public:
    struct node
    {
        Quantum Item;
        node* next;
        node(Quantum data)
        {
            Item.eventID = data.eventID;
            Item.size = data.size;
            Item.eventBuff = data.eventBuff;
            next=0;
        };
    };

    node *head, *tail;
    CActionQueue();
    ~CActionQueue();
    Quantum Get();
    void Put(Quantum);
    int IsEmpty();
};

#endif	/* _ACTIONQUEUE_H */

