#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <ncurses.h>

WINDOW* init_window();
void clean(int env, void* arg);

#endif