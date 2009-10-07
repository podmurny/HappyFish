/*
Здесь находятся функции утилиты для работы с BSD сокетами.
create_addr - получает ссылку на переменную типа sockaddr_in и заполняет эту структур
Bind - устанвливает для использования указаный адрес
Listen - делает из сокета слушающий соккет
Connect - соеденяет указаный сокет с сокетом на сервере 
*/
#ifndef _GSG_SOCKET_

#define _GSG_SOCKET_

#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<cstring>
#include<stdio.h>
#define NOT_ACTIV_CONN_COUNT 5
#define FOREVER for(;;)

int create_addr(struct sockaddr_in&  addr, const char* ipstr, const short int port);
/*WARNING:*/
/*Функции Bind и Connect в качестве аргументов должны получить ссылку на структуру    sockaddr_in.
  Эта структура может быть уже с указанным адресом и номером порта, ipstr и port указывать не надо.
  Но если вы хотите создать новую структуру, то явно укажите эти аргументы.    По умолчанию   они 
  указаны как NULL*/
int Bind(struct sockaddr_in& addr, int sock_fd, const char* ipstr = NULL, const short int port = -1);
int Connect(struct sockaddr_in& addr, int sock_fd, const char* ipstr = NULL, const short int port = -1);
int Listen(int& sock_fd);
#endif
