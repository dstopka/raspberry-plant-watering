#ifndef _VALVE_CONTROL_H_
#define _VALVE_CONTROL_H_

#include "valve_state.h"

#define VALVE_PIN 0

void init_valve_control();
void trigger_valve();
valve_state get_valve_state();

#endif