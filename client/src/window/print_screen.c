#include "print_screen.h"

void
print_humidity(WINDOW* window, double val)
{
    clear_line(window, HUMIDITY_INFO_ROW);
    mvwprintw(window, HUMIDITY_INFO_ROW, (int)(5), "Humidity: %.2f%%", val);
}

void
print_valve_state(WINDOW* window, valve_state state)
{
    char* state_string = valve_state_string(state);
    mvwprintw(window, VALVE_INFO_ROW, (int)(5), "Valve state: %s", state_string);
}

void
print_pump_power(WINDOW* window, double power)
{
    clear_line(window, PUMP_POWER_ROW);
    mvwprintw(window, PUMP_POWER_ROW, (int)(5), "Pump power: %.2f%%", power);
}

void
clear_line(WINDOW* window, int line)
{
    wmove(window, line, 0);
    wclrtoeol(window); 
}