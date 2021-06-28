#include <wiringPi.h>
#include <stdlib.h>
#include <unistd.h>

#include "gpio_helpers.h"
#include "trace.h"

void
init_gpio()
{
    if(wiringPiSetup() < 0)
    {
        TRACE_ERROR("wiringPi setup failed");
        _exit(EXIT_FAILURE);
    }

    TRACE_INFO("wiringPi setup successfully");
}