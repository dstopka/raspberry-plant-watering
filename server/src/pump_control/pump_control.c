#include <wiringPi.h>

#include "pump_control.h"
#include "trace.h"

#define MIN_POWER 0
#define MAX_POWER 1024
#define POWER_STEP 128

static void set_pump_power(int power);

static volatile int pump_power = MIN_POWER;

void
init_pump_control()
{
    pinMode(PUMP_PIN, PWM_OUTPUT);
    set_pump_power(MIN_POWER);
}

void
pump_power_up()
{
    set_pump_power(pump_power + POWER_STEP);
}

void
pump_power_down()
{
    set_pump_power(pump_power - POWER_STEP);
}

double
get_pump_power()
{
    return (double)pump_power / MAX_POWER * 100;
}

void
set_pump_power(int power)
{
    if(power < MIN_POWER || power > MAX_POWER)
    {
        TRACE_INFO("Pump power = %d is out of range. No action.", power);
        return;
    }

    pwmWrite(PUMP_PIN, power);
    TRACE_INFO("Pump power set successfully. %d -> %d", pump_power, power);
    pump_power = power;
}