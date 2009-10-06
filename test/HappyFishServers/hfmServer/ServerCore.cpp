#include "ServerCore.h"

CServerCore::CServerCore()
  :listenSocket(-1), maxSocketNumber(0), valid(DISCONNECT)
{
  bzero(&serverAddr,sizeof(serverAddr));
}

CServerCore::~CServerCore()
{
  close(listenSocket);
}

void CServerCore::SetMaxSocketNumber(int &int_msn, int int_currentSocketNumber, bool bool_connect)
{
    /*
     * Для функции SELECT необходимо знать максимальное значение дескрипторов сокетов,
     * среди которых она выберает.
     * Разумется это значение может изменятся при каждом подключение или отключение
     * пользователя. И для того что б контролировать это значение я написал эту функцию.
     * НО ЭТА ФУНКЦИЯ ПРИ БОЛЬШОМ КОЛИЧЕСТВЕ ПОДКЛЮЧЕНИЙ БУДЕТ РАБОТАТЬ НЕ ВЕРНО!!!
     * поэтому нам нужно предумать более правильный механизм контроля максимального
     * значения дескрипторов сокетов.
     */
  if(bool_connect)
    {
      if(int_currentSocketNumber > int_msn)
	int_msn = int_currentSocketNumber;
    }
  else
    {
      if(int_currentSocketNumber == int_msn)
	int_msn--;
    }
}

int CServerCore::Recend(string fromStr)
{
  char* chPtr = strchr(buf, int('*'));
  if(chPtr == NULL)
    {
      return -1;
    }
  chPtr[0] = '\0'; chPtr++;
  
  int receiverID = userList.GetSock(buf);
  cout<<"Message:("<<chPtr<<") from "<<fromStr<<" to "<<buf<<endl;
  
  string str(chPtr);
  str = fromStr + "*" + str;
  if(send(receiverID, str.data(), 1024, 0) < 0)
    return -1;
  return 0;
}

void CServerCore::Authorize(int sockNum, char* lbuf)   //Logon user
{
  cout<<"========================================="<<endl;
  cout<<"User whith socket number "<<sockNum<<" try login"<<endl;
  cout<<"This user send string: "<<lbuf<<endl;

  char* chPtr;
  chPtr = strchr(lbuf, int('*'));
  if(chPtr == NULL)
    {
      cout<<"invalid user string"<<endl;
      cout<<"connection "<<sockNum<<" close"<<endl;
      cout<<"========================================="<<endl;
      userList.DeleteRecord(sockNum);
      close(sockNum);
      return;
    }
  chPtr[0] = '\0'; chPtr++;
  hfm_db db;
  cout<<"User name: "<<lbuf<<endl<<" Pass: "<<chPtr<<endl;
  if(db.logon_user(lbuf, chPtr) == 0)
    {
      cout<<"LOGIN - OK"<<endl;
      userList.ChangeName(sockNum, lbuf);
      char ok[] = "OK";
      send(sockNum, ok, sizeof(ok), 0);
      cout<<"========================================="<<endl;
    }
  else
    {
      cout<<"LOGIN - NOT OK!!"<<endl;
      cout<<"connection "<<sockNum<<" close"<<endl;
      cout<<"========================================="<<endl;
      userList.DeleteRecord(sockNum);
      close(sockNum);
    }
}

int CServerCore::Routing(int sockNum)
{
  bzero(buf,sizeof(buf));
  int bytes_read = recv(sockNum, buf, 1024, 0);
  if(bytes_read <= 0)
    {
      cout<<"========================================="<<endl;
      cout<<"User "<<userList.GetName(sockNum)<<" exit"<<endl;
      cout<<"Connection #"<<sockNum<<" close"<<endl;
      cout<<"========================================="<<endl;
      close(sockNum);
      userList.DeleteRecord(sockNum);
      return 0;
    }
  
  string checkStr = userList.GetName(sockNum);

  if(checkStr == "NOSOCK")
    {
      return -1;
    }
  if(checkStr == "NONE")
    {
      Authorize(sockNum, buf);
      return 0;
    }

  cout<<"========================================="<<endl;
  cout<<"Message from "<<checkStr<<": "<<buf<<endl;
  if(Recend(checkStr) == -1)
  {
      cout<<"========================================="<<endl;
      return -1;
  }
  cout<<"========================================="<<endl;
  return 0;
}

void CServerCore::NewConnection()
{
    cout<<"========================================="<<endl;
    cout<<"New connection"<<endl;
    int sock = accept(listenSocket, NULL, NULL);
    if(sock < 0)
    {
      perror("accept");
    }
    cout<<"New socket number: "<<sock<<" - NOT LOGIN!!!"<<endl;
    fcntl(sock, F_SETFL, O_NONBLOCK);
    SetMaxSocketNumber(maxSocketNumber, sock, true);
    userList.AddRecord("NONE", sock);
    cout<<"========================================="<<endl;
    cout<<"good action"<<endl;
}

int CServerCore::Init(int port)
{
  serverPort = port;
  listenSocket = socket(AF_INET, SOCK_STREAM, 0);
  if(listenSocket <= 0)
    {
      return -1;
    }
  fcntl(listenSocket, F_SETFL, O_NONBLOCK);
  
  if(Bind(serverAddr, listenSocket, "any", 6000) < 0)
    {
      perror("Bind");
      return -1;
    }
  if(Listen(listenSocket) < 0)
    {
      return -1;
    }
  maxSocketNumber = listenSocket;
  valid = CONNECT;
  cout<<"Server start 0K"<<endl;
  return 0;
}

int CServerCore::Start()
{
  fd_set readset;
  ptr listIter;
  while(1)
    {
      FD_ZERO(&readset);
      FD_SET(listenSocket, &readset); 
      for(listIter = userList.GetHead(); listIter != NULL; listIter = listIter->next)
	{
	  FD_SET(listIter->item.sock_n, &readset);
	}
      timeval timeout;
      timeout.tv_sec = 15;
      timeout.tv_usec = 0;
      if(select(maxSocketNumber + 1, &readset, NULL, NULL, &timeout) <= 0)
	{
	  continue;
	}
       //Проверка всех сокетов
      if(FD_ISSET(listenSocket,&readset))	//Если ктото ломится к листенеру
	{
	  // Поступил новый запрос на соединение, используем accept
          NewConnection();
	}
      for(listIter = userList.GetHead(); listIter != NULL; listIter = listIter->next)
        {
	  if(FD_ISSET(listIter->item.sock_n, &readset))	//Если на порт данного сокета ктото ломится
	    if(Routing(listIter->item.sock_n) < 0)
	      cout<<"invalid routing"<<endl;
            else
                cout<<"good action"<<endl;
	}
    }
  return 0;
}
