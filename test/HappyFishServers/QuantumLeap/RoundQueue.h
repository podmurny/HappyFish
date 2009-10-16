/* 
 * File:   RoundQueue.h
 * Author: otherside
 *
 * Created on October 16, 2009, 1:04 PM
 */

#ifndef _CROUNDQUEUE_H
#define	_CROUNDQUEUE_H
#include <cstring>

#define QUANTUM_BUF_SIZE 1024

struct Quantum  //структура в которой находится сообытие
{
    short int eventID; //индитификатор события
    int size;          //рфзмер буфера с данными события
    char eventBuff[QUANTUM_BUF_SIZE];//буфер с данными события
    Quantum()
    {
        eventID = 0;
        size = 0;
    }
   //мы можем создать событи в котором будут сразу хранится какието данные
    Quantum(short int ID, short int bufSize, void* cPtr, short bytes)
    {
        eventID = ID;
        size = bufSize;
        memcpy(this->eventBuff, cPtr, bytes);
    }
    //для удобства работы с добовлениям событий в круговую очередь пришлось
    //перегрузить оператор присваивания для этой структуры
    const Quantum &operator=(const Quantum &right)//см. Дейтел
    {
        if(&right != this)
        {
            this->eventID = right.eventID;
            this->size = right.size;
            /*
             * eventBuff - это не масив чаров!!! это просто указатель на первый
             * элемент массива чаров.
             * Поэтому, если б мы не перегружали оператор присваивания, то при присваивании
             * от одного экземпляра структуры другому эксземпляру передавался б только указатель на маасив.
             * А нам надо скопировать сразу все элементы этого буфера, для коректного создания нового элемента.
             */
            memcpy(this->eventBuff, right.eventBuff, QUANTUM_BUF_SIZE);
        }
        return *this;
    }
};

//Изначально ксласс CRoundQueue был шаблонным, и служил клнтейнером для обьектов класса Item
typedef Quantum Item;//Таким образом что б не минять везде Item на Quantum, я просто добавил это определние
//Везде где в классе CRoundQueue ты видиш Item, компилятор видет Quantum


/*
 * А вот и собственно класс круговой очереди.
 * Возможности:
 * 1)пользователь этого может добовлять в очередь экземпляры Quantum
 * 2)просматривать текущий элемент
 * 3)переходить на следующий элемент
 * Перемещение указателе по эелементам происходит по кругу.
 */
class CRoundQueue
{
private:
    struct node//Структура для хранения текущего экземпляра Quantum
    {
        Item item;//экземпляр Quantum
        node* next;//Поскольку у нас крговая очередь то нам надо указатеди на слудующий
        node* prev;//и предведущий элементы
        node(Item data)
        {
            item = data;
            next = 0;
            prev = 0;
        }
    };
private:
    node* current;//указатель на текущий элемент

public:
    CRoundQueue();
    ~CRoundQueue();
    void Add(Item &data);//добавит в круговую очередь событий новое событие
    void Delete();//удалить текущие событие и перейти на следующие(если оно есть)
    Item* GetCurrentPointer();//получить указатель на текущие событие(экземпляр Quantum)
    bool IsEmpty();
    void Next();//перейти на следующие елемент
};

#endif	/* _CROUNDQUEUE_H */

