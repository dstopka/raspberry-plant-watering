#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#include "print_lcd.h"
#include "i2c_helpers.h"
#include "trace.h"
#include "pump_control.h"
#include "valve_control.h"
#include "valve_state.h"
#include "humidity_sensor.h"

static void print_lcd(const int fd, char* str, size_t n);
static void print_valve_state(const int fd, const valve_state state);
static void print_pump_power(const int fd, const double power);
static void print_humidity(const int fd, const double val);

void
update_lcd(const int fd)
{
    i2c_point_to_addr(fd, LCD_ADDR);

    LCM_write_command(fd, 0x01);

    usleep(1000);

    double power = get_pump_power();
    valve_state state = get_valve_state();
    double humidity = get_humidity();

    print_pump_power(fd, power);
    print_valve_state(fd, state);
    print_humidity(fd, humidity);

    TRACE_DEBUG("LCD updated {humidity = %.2f%%, valve_state = %d, pump_power = %.2f%%}", humidity, state, power);
}

void
print_valve_state(const int fd, const valve_state state)
{
    char str[5];
    if(sprintf(str, "V: %c", state + 48) < 0)
    {
        TRACE_WARNING("Sprintf failed with errno = %d", errno);
    }

    LCM_write_command(fd, SECOND_LINE);
    print_lcd(fd, str, strlen(str));
}

void
print_pump_power(const int fd, const double power)
{
    char str[11];
    if(sprintf(str, "P: %.2f%%", power) < 0)
    {
        TRACE_WARNING("Sprintf failed with errno = %d", errno);
    }

    LCM_write_command(fd, SECOND_LINE + 6);
    print_lcd(fd, str, strlen(str));
}

void
print_humidity(const int fd, const double val)
{
    char str[18];
    if(sprintf(str, "Humidity: %.2f%%", val) < 0)
    {
        TRACE_WARNING("Sprintf failed with errno = %d", errno);
    }

    // i2c_point_to_addr(fd, LCD_ADDR);
    LCM_write_command(fd, FIRST_LINE);
    print_lcd(fd, str, strlen(str));
}

void
print_lcd(const int fd, char* str, size_t n)
{
    for (size_t i = 0; i < n; ++i)
    {
        LCM_write_data(fd, str[i]);
    }

    usleep(1000);
}