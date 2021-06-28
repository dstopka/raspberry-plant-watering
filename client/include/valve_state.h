#ifndef _VALVE_STATE_H_
#define _VALVE_STATE_H_

typedef enum valve_state {
    VALVE_OPENED = 1,
    VALVE_CLOSED = 0
} valve_state;

char* valve_state_string(valve_state state);
valve_state valve_state_from_int(int state);

#endif