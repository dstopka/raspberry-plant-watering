#include "window.h"
#include "trace.h"

WINDOW*
init_window()
{
    initscr();

    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    cbreak();
    refresh();

    WINDOW* window = newwin(LINES, COLS, 0, 0);      

    noecho();
    keypad(window, TRUE);
    curs_set(0);
    wattron(window, COLOR_PAIR(1));
    wbkgdset(window, COLOR_PAIR(1));
   
    wclear(window);
    wrefresh(window);

    box(window, 0, 0);

    on_exit(clean, NULL);

    return window;
}

void
clean(int env, void* arg)
{
    (void)env;
    (void)arg;
    // delwin(window);
    printf("BYEBYE\n");
    endwin();
    system("clear");
}