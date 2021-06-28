#ifndef _RESPONSE_HANDLING_H_
#define _RESPONSE_HANDLING_H_

#include "response.h"

response trigger_valve_response(valve_state state);
response get_valve_state_response(valve_state state);
response get_humidity_response(double val);
response pump_up_response(double power);
response pump_down_response(double power);
response get_pump_power_response(double power);

#endif