#include <stdio.h>

#include "request_handling.h"
#include "response_handling.h"
#include "valve_control.h"
#include "print_lcd.h"
#include "humidity_sensor.h"
#include "pump_control.h"

response
handle_request(request_handler handler, request request, const int i2c_fd)
{
    response resp;

    switch (request.type)
    {
    case GET_HUMIDITY:
    {
        resp = handler.get_humidity(i2c_fd);
        break;
    }
    case TRIGGER_VALVE:
    {
        resp = handler.trigger_valve();
        break;
    }
    case GET_VALVE_STATE:
    {
        resp = handler.get_valve_state();
        break;
    }
    case GET_PUMP_POWER:
    {
        resp = handler.get_pump_power();
        break;
    }
    case PUMP_UP:
    {
        resp = handler.pump_power_up();
        break;
    }
    case PUMP_DOWN:
    {
        resp = handler.pump_power_down();
        break;
    }
    default:
        break;
    }

    return resp;
}

request_handler
make_request_handler()
{
    request_handler handler;

    handler.get_humidity = &get_humidity_handler;
    handler.get_pump_power = &get_pump_power_handler;
    handler.get_valve_state = &get_valve_state_handler;
    handler.pump_power_down = &pump_power_down_handler;
    handler.pump_power_up = &pump_power_up_handler;
    handler.trigger_valve = &trigger_valve_handler;

    return handler;
}

response
get_humidity_handler(const int i2c_fd)
{
    measure_humidity(i2c_fd);
    double val = get_humidity(i2c_fd);    
    return get_humidity_response(val);
}

response
get_valve_state_handler()
{
    valve_state state = get_valve_state();
    return get_valve_state_response(state);
}

response
get_pump_power_handler()
{
    double power = get_pump_power();
    return get_pump_power_response(power);
}

response
pump_power_up_handler()
{
    pump_power_up();
    double power = get_pump_power();
    return pump_up_response(power);
}

response
pump_power_down_handler()
{
    pump_power_down();
    double power = get_pump_power();
    return pump_down_response(power);
}

response
trigger_valve_handler()
{
    trigger_valve();
    valve_state state = get_valve_state();
    return trigger_valve_response(state);
}