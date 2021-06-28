#ifndef _PRINT_SCREEN_H_
#define _PRINT_SCREEN_H_

#define HUMIDITY_INFO_ROW 5
#define VALVE_INFO_ROW 6
#define PUMP_POWER_ROW 7

#include <ncurses.h>

#include "valve_state.h"

void print_humidity(WINDOW* window, double val);
void print_valve_state(WINDOW* window, valve_state state);
void print_pump_power(WINDOW* window, double power);
void clear_line(WINDOW* window, int line);

#endif