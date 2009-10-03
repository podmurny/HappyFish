#include "NetworkClient.h"
#include "gsg_text_client.h"
#include <stdlib.h>
#include <unistd.h>

void InitTextClient(XYcords &cords)
{
  cbreak();
  start_color();
  refresh();
  getmaxyx(stdscr, cords.ymax, cords.xmax);
  noecho();
}

void* NetworkListen(void* client_void)
{
  NetworkClient* client = (NetworkClient*)client_void;
  if(client->GetValid() == DISCONNECT)
    return NULL;
  char buf[1024];
  XYcords xy;
  XYcords prexy;
  xy.xmax = 1;
  xy.ymax = 1;
  while(1)
    {
      getyx(swin, prexy.ymax, prexy.xmax);
      if(client->WaitMsg(buf, sizeof(buf))>0)
	if(!pthread_mutex_lock(&lockx))
	  {
	    mvwprintw(bwin, xy.ymax, xy.xmax, buf);
	    mvwprintw(swin, 1, 1, temp.data());
	    wrefresh(bwin);
	    wrefresh(swin);
	    pthread_mutex_unlock(&lockx);
	  }
    }
}

int StartNetworkListen(void* cl)
{
  pthread_t recvThr;		//Message receive thread id
  if(pthread_create(&recvThr,0,&NetworkListen,cl) == -1)
    return -1;
  return 0;
}

void GetUserString(std::string &str)
{
  keypad(stdscr, TRUE);
  str = "";
  temp = "";
  char ch;
  while(1)
    {
      ch = getch();
      if(ch == '\n')
	break;
      if(ch == '\a')
	{
	  std::string ltemp = "";
	  for(int i = 0; i < str.length() - 1; i++)
	    ltemp += str[i];
	  str = ltemp;
	  ltemp = "";
	  for(int i = 0; i < temp.length() - 1; i++)
	    ltemp += temp[i];
	  temp = ltemp;
	  if(!pthread_mutex_lock(&lockx))
	    {
	      DeleteChar(swin);
	      wrefresh(swin);
	      pthread_mutex_unlock(&lockx);
	    }
	}
      else
	{
	  str += ch;
	  if(!pthread_mutex_lock(&lockx))
	    {
	      temp += ch;
	      waddch(swin, ch);
	      wrefresh(swin);
	      pthread_mutex_unlock(&lockx);
	    }//end of mutex
	}//end of if
    }//end of while
}

void StartNetworkSend(NetworkClient* client)
{
  std::string str;
  while(1)
    {
      sleep(1);
      str = "";
      GetUserString(str);
      client->SendMsg(str);
      wclear(swin);
      box(swin, 0 , 0);
      wmove(swin, 1, 1);
      wrefresh(swin);
    }
}
