#ifndef NSCREEN
#define NSCREEN

#include <ncurses.h>

WINDOW *create_newwin_box(int height, int width, int starty, int startx);
void DeleteChar(WINDOW* win);
#endif
