#include "gsg_nscreen.h"

WINDOW *create_newwin_box(int height, int width, int starty, int startx)
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

void DeleteChar(WINDOW* win)
{
  int x,y;
  getyx(win, y, x);
  if(x >= 2)
    {
      mvwprintw(win, y, x - 1, " ");
      wmove(win, y, x - 1);
    }
}
