#include "response_handling.h"

response 
trigger_valve_response(valve_state state)
{
    response resp;
    resp.type = TRIGGER_VALVE;
    resp.v_state = state;
    return resp;
}

response 
get_valve_state_response(valve_state state)
{
    response resp;
    resp.type = GET_VALVE_STATE;
    resp.v_state = state;
    return resp;
}

response 
get_humidity_response(double val)
{
    response resp;
    resp.type = GET_HUMIDITY;
    resp.humidity = val;
    return resp;
}

response
pump_up_response(double power)
{
    response resp;
    resp.type = PUMP_UP;
    resp.power = power;
    return resp;
}

response
pump_down_response(double power)
{
    response resp;
    resp.type = PUMP_DOWN;
    resp.power = power;
    return resp;
}

response
get_pump_power_response(double power)
{
    response resp;
    resp.type = GET_PUMP_POWER;
    resp.power = power;
    return resp;
}