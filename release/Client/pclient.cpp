#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "libsock.h"

char buf[1024];

WINDOW *create_newwin(int height, int width, int starty, int startx)
{	
  WINDOW *local_win;
  local_win = newwin(height, width, starty, startx);
  init_pair(1, COLOR_WHITE, COLOR_BLUE);
  wbkgdset(local_win,COLOR_PAIR(1)); 
  wclear(local_win);
  box(local_win, 0 , 0);	   
  wrefresh(local_win);
  return local_win;
}

void Draw_Screen(WINDOW *one, WINDOW *two, int row, int col)
{

  one = create_newwin(row - 10, col, 0, 0);
  two = create_newwin(10, col, row - 10, 0);
}

void read_and_send(int sock, WINDOW *win)
{
  mvwprintw(win,1,1,"Enter message: ");
  wrefresh(win);
  wgetstr(win,buf);
  send(sock,buf, 1024, 0);
  wbkgdset(win,COLOR_PAIR(1)); 
  wclear(win);
  box(win, 0 , 0);	   
  wrefresh(win);
}

void recv_and_write(int sock, WINDOW *win, WINDOW *owin, int &k)
{
  if(k > 8)
	{
	wbkgdset(win,COLOR_PAIR(1)); 	  
	wclear(win);
	box(win, 0 , 0);	   
  	wrefresh(win);
	k = 2;
	}	
  int x,y;
  getyx(owin, x, y);
  bzero(buf,sizeof(buf));
  int bytes_read = recv(sock, buf, 1024, 0);
  if(bytes_read >= 0)
	{
  		mvwprintw(win, k, 1, "Msg:");
		mvwprintw(win, k, 6, buf);
	}
  k++;
  wrefresh(win);
  wmove(owin,1,16);
  wrefresh(owin);
}

int row,col;

int main(int argc, char *argv[])
{
  if(argc != 2)
	exit(1);
  initscr();	/* Start curses mode */
  cbreak();
  start_color();
  init_pair(1, COLOR_RED, COLOR_BLUE);
  refresh();   /*end initial screen*/
  
  getmaxyx(stdscr,row,col);/* get the number of rows and columns */
  WINDOW* fwin;
  WINDOW* swin;
  fwin = create_newwin(row - 10, col, 0, 0);
  swin = create_newwin(10, col, row - 10, 0);
  
  /*Initial network*/
  int sock;
  sockaddr_in addr;
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if(sock <= 0){
    mvwprintw(fwin,2,2,"Socket not work");
    wrefresh(fwin);
    getch();
    endwin();
    exit(1);
  }
  if(Connect(addr, sock, argv[1], 6000) < 0){
    mvwprintw(fwin,2,2,"Connect not work");
    wrefresh(fwin);
    getch();
    endwin();
    exit(1);
  }
  /*End initial network*/
 
  /*main part of client*/
  int k = 1;
  switch(fork())
    {
    case (pid_t)-1:
      mvwprintw(fwin,2,2,"Fork not work");
      wrefresh(fwin);
      getch();
      endwin();
      exit(1);
      break;
    case (pid_t)0:
      while(1)
	{
	  recv_and_write(sock, fwin, swin, k);
	}
      exit(1);
      break;
    default:
      FOREVER //FUCK YOU!!!
	read_and_send(sock, swin);
      break;
    }
  /*end client*/
  
  wmove(swin,3,3);
  getch();
  endwin();	/* End curses mode */
  close(sock);
  return 0;
}


