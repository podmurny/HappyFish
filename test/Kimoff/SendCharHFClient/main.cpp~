#include "NetworkClient.h"
#include <iostream>
#include <termios.h>	//To change terminal input mode
#include <stdlib.h>
#include <pthread.h>
#include <string>
#include "gsg_text_client.h"
using namespace std;

NetworkClient client;
pthread_mutex_t lockx;
XYcords cords;
WINDOW* bwin;
WINDOW* swin;
std::string temp;

int main(int argc, char *argv[])
{
  initscr();
  InitTextClient(cords);
  bwin = create_newwin_box(cords.ymax - 10, cords.xmax, 0, 0);
  swin = create_newwin_box(10, cords.xmax, cords.ymax - 10, 0);

  void* cl = (void*)&client;
  
  client.ConnectToServer(6002,"localhost");
  if(client.GetValid() == DISCONNECT){
    mvwprintw(bwin, 1, 1, "ERROR: Network not work");
    wrefresh(bwin);}

  if(pthread_mutex_init(&lockx, 0)){
    mvwprintw(bwin, 1, 1, "ERROR: Mutex not work");
    wrefresh(bwin);}
  
  if(StartNetworkListen(cl)){
    mvwprintw(bwin, 1, 1, "ERROR: Thread not work");
    wrefresh(bwin);}
  
  wmove(swin, 1, 1);
  wrefresh(swin);
  
  StartNetworkSend(&client);
  
  if(pthread_mutex_destroy(&lockx)){
    mvwprintw(bwin, 1, 1, "ERROR: Mutex not work");
    wrefresh(bwin);}
  
  client.Disconnect();
  
  endwin();	/* End curses mode */
  return 0;
}
