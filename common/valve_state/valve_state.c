#include "valve_state.h"

char*
valve_state_string(valve_state state)
{
    char* state_string;
    
    switch(state)
    {
    case VALVE_OPENED:
        state_string = "Opened";
        break;
    case VALVE_CLOSED:
        state_string = "Closed";
        break;    
    default:
        break;
    }

    return state_string;
}

valve_state
valve_state_from_int(int state)
{
    if(state == 0)
    {
        return VALVE_CLOSED;
    }

    return VALVE_OPENED;
}