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

void* NetworkListen(void* client_void)		//Listening for receiving messages
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
		if (buf == "BACKSPACE")		//Send BACKSPACE to receiver client
		{
			DeleteChar(bwin);		//Delete last symbol from the screen
			wrefresh(bwin);
		}
		else mvwprintw(bwin, xy.ymax, xy.xmax, buf);
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

//////////////ОПТИМИЗИРОВАТЬ ЭТО ГАВНО!!!!!!!
void GetUserString(std::string &str, NetworkClient* client)
{
  keypad(stdscr, TRUE);
  str = "";
  temp = "";
  char ch;
  while(1)
    {
      	ch = getch();
      	if(ch == '\n')	//ENTER
	{
		str = "ENTER";		
		client->SendMsg(str);	
		break;				//Stop inputing string
	}
     	if(ch == '\a')	//BACKSPACE
	{
		str = "BACKSPACE";		//Send BACKSPACE to receiver client
		//client->SendMsg(str);
		if(!pthread_mutex_lock(&lockx))
	    	{
	      		DeleteChar(swin);		//Delete last symbol from the screen
	      		wrefresh(swin);
	      		pthread_mutex_unlock(&lockx);
	    	}

	}
      	else
	{
	  str = ch;				//Send entered symbol
	  if(!pthread_mutex_lock(&lockx))
	    {
	      waddch(swin, ch);
	      wrefresh(swin);
	      pthread_mutex_unlock(&lockx);
	    }//end of mutex
	}//end of if
	client->SendMsg(str);			//Send message (entered char or BACKSPACE command)
    }//end of while
}

void StartNetworkSend(NetworkClient* client)
{
  std::string str;
  while(1)
    {
      //sleep(1);
      str = "";
      GetUserString(str, client);
      //client->SendMsg(str);
      wclear(swin);		//Clear the window
      box(swin, 0 , 0);		//Draw РАМКУ around the window
      wmove(swin, 1, 1);	//Cursor to start position
      wrefresh(swin);		//Refresh the window on the screen
    }
}
