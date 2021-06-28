#ifndef _PUMP_CONTROL_H_
#define _PUMP_CONTROL_H_

#define PUMP_PIN 1

void init_pump_control();
void pump_power_up();
void pump_power_down();
double get_pump_power();

#endif