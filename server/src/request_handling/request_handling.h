#ifndef _REQUEST_HANDLING_H_
#define _REQUEST_HANDLING_H_

#include "request.h"
#include "response.h"

typedef struct request_handler {
    response (*get_humidity)(const int);
    response (*get_valve_state)();
    response (*get_pump_power)();
    response (*pump_power_up)();
    response (*pump_power_down)();
    response (*trigger_valve)();
} request_handler;

request_handler make_request_handler();
response handle_request(request_handler handler, request request, const int i2c_fd);
response get_humidity_handler();
response get_valve_state_handler();
response get_pump_power_handler();
response pump_power_up_handler();
response pump_power_down_handler();
response trigger_valve_handler();

#endif