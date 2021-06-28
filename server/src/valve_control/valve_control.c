#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

#include "valve_control.h"
#include "valve_state.h"
#include "trace.h"

static volatile int valve_opened = 0;

static void open_valve();
static void close_valve();

void
init_valve_control()
{
    pinMode(VALVE_PIN, OUTPUT);
    close_valve();
}

void
open_valve()
{
    digitalWrite(VALVE_PIN, HIGH);
}

void
close_valve()
{
    digitalWrite(VALVE_PIN, LOW);
}

void
trigger_valve()
{
    if(valve_opened)
    {
        close_valve();
    } 
    else 
    {
        open_valve();
    }

    valve_opened = !valve_opened;
    TRACE_INFO("Valve triggered. State = %d", valve_opened);
}

valve_state
get_valve_state()
{
    // return valve_state_from_int(valve_opened);
    return valve_opened;
}