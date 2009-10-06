#ifndef SERVERCORE
#define SERVERCORE
/*
 * Если б кто только знал как я уже заебался коментировать свой код...
 * Собственно этот класс и есть сервер.
 * Этот класс разрабатывали: Станислав Кимов, Илья Музычук
 */
#include "gsg_socket.h"  //Используем вспомогательные функции по роботе с сокетами
#include "SocketTable.h" //Используем клас таблици пользователей
#include "CDBClient.h"   //Класс для работы с базой данных
#include <unistd.h>
#include <fcntl.h>       //Используем функции для асинхронного вода/вывода(мультеплексирования)
#include <iostream>
#include <string.h>
using namespace std;

#define CONNECT 1        //Макросы состояния сервера
#define DISCONNECT 0

class CServerCore
{

private:
  int listenSocket;              //Дескриптор слушающего сокета
  sockaddr_in serverAddr;        //Адресс сервера в сети
  int maxSocketNumber;           //Максимальное значение дескриптора сокета см. SetMaxSocketNumber
  int valid;                     //Состояние сокета(CONNECT/DISCONNECT)
  CSocketTable userList;         //Список пользователей
  int serverPort;                //Порт сервера
  char buf[1024];                //В это буфер записуем данные полученые от клиентов
                                 //все клиенты использують общий буфер (экономим память:))
private:
  int Routing(int sockNum);      //Ну эта функция делает, то, о чём говорит её название
  // SetMaxSocketNumber - ОЧЕНЬ МУТНАЯ ФУНКЦИЯ
  void SetMaxSocketNumber(int &int_msn, int int_currentSocketNumber, bool bool_connect);
  void Authorize(int sockNum, char* lbuf);//Авторизация пользователя
  int Recend(string fromStr);    //Пересылка сообщения
  void NewConnection();          //Подключение пользователя
public:
  CServerCore();
  ~CServerCore();
  int Init(int port);            //Для начала сервер нужно проинициализировать
  int Start();                   //А только потом запускать
  
};

#endif
