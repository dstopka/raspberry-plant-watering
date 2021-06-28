#include "response_handling.h"

void
handle_response(response_handler handler, response resp, WINDOW* window)
{
    switch(resp.type)
    {
    case GET_HUMIDITY:
        handler.get_humidity_handler(window, resp.humidity);
        break;
    case TRIGGER_VALVE:
    case GET_VALVE_STATE:
        handler.trigger_valve_handler(window, resp.v_state);
        break;    
    case PUMP_UP:
    case PUMP_DOWN:
    case GET_PUMP_POWER:
        handler.pump_action_handler(window, resp.power);
        break;
    default:
        break;
    }
}