#ifndef _RESPONSE_HANDLING_H_
#define _RESPONSE_HANDLING_H_

#include <ncurses.h>

#include "response.h"

typedef struct response_handler {
    void (*get_humidity_handler)(WINDOW*, double);
    void (*trigger_valve_handler)(WINDOW*, valve_state);
    void (*pump_action_handler)(WINDOW*, double);
} response_handler;

void handle_response(response_handler handler, response resp, WINDOW* window);

#endif