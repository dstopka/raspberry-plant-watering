#include <unistd.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <errno.h>

#include "lcd.h"
#include "i2c_helpers.h"
#include "valve_control.h"
#include "print_lcd.h"
#include "humidity_sensor.h"
#include "pump_control.h"
#include "trace.h"

static int write_nibble_to_control_register(int fd, unsigned char val);
static int write_nibble_to_data_register(int fd, unsigned char val);
static int LCD_init(int fd);

void
init_lcd(const int fd)
{
    if(LCD_init(fd) < 0)
    {
        TRACE_ERROR("LCD init failed");
        _exit(EXIT_FAILURE);
    }

    TRACE_INFO("LCD init successful");

    update_lcd(fd);
}

int
write_nibble_to_control_register(int fd, unsigned char val)
{
    unsigned char high_nibble;
    unsigned char loc;

    high_nibble = (0xF0 & val);
    loc = ((high_nibble | (1 << 2)) | BACKLIGHT);
    if(write(fd, &loc, 1) < 0)
    {
        TRACE_ERROR("Writing to %d failed with code %d", fd, errno);
        return -1;
    }

    usleep(LCD_WRITE_DELAY);

    loc = (high_nibble | BACKLIGHT);
    if(write(fd, &loc, 1) < 0)
    {
        TRACE_ERROR("Writing to %d failed with code %d", fd, errno);
        return -1;
    }

    usleep(LCD_WRITE_DELAY);

    return 0;
}

int
write_nibble_to_data_register(int fd, unsigned char val)
{
    unsigned char high_nibble;
    unsigned char loc;

    high_nibble = (0xF0 & val);
    loc = ((high_nibble | (1 << 2)) | BACKLIGHT | DATA_REGISTER);
    if(write(fd, &loc, 1) < 0)
    {
        TRACE_ERROR("Writing to %d failed with code %d", fd, errno);
        return -1;
    }

    usleep(LCD_WRITE_DELAY);

    loc = (high_nibble | BACKLIGHT | DATA_REGISTER);
    if(write(fd, &loc, 1) < 0)
    {
        TRACE_ERROR("Writing to %d failed with code %d", fd, errno);
        return -1;
    }

    usleep(LCD_WRITE_DELAY);

    return 0;
}

int
LCM_write_command(int fd, unsigned char val)
{
    unsigned char high_nibble;
    unsigned char low_nibble;

    high_nibble = (0xF0 & val);
    if(write_nibble_to_control_register(fd, high_nibble) < 0)
    {
        TRACE_WARNING("Writing to control register failed");
        return -1;
    }

    low_nibble = ((0x0F & val) << 4);
    if(write_nibble_to_control_register(fd, low_nibble) < 0)
    {
        TRACE_WARNING("Writing to control register failed");
        return -1;
    }

    return 0;
}

int
LCM_write_data(int fd, unsigned char val)
{
    unsigned char high_nibble;
    unsigned char low_nibble;

    high_nibble = (0xF0 & val);
    if(write_nibble_to_data_register(fd, high_nibble) < 0)
    {
        TRACE_WARNING("Writing to data register failed");
        return -1;
    }

    low_nibble = ((0x0F & val) << 4);
    if(write_nibble_to_data_register(fd, low_nibble) < 0)
    {
        TRACE_WARNING("Writing to data register failed");
        return -1;
    }

    return 0;
}

int
LCD_init(int fd)
{
    i2c_point_to_addr(fd, LCD_ADDR);

    if(write_nibble_to_control_register(fd, 0x30) < 0)
    {
        return -1;
    }

    usleep(4500);

    if(write_nibble_to_control_register(fd, 0x30) < 0)
    {
        return -1;
    }

    usleep(150);

    if(write_nibble_to_control_register(fd, 0x30) < 0)
    {
        return -1;
    }

    usleep(100);

    if(write_nibble_to_control_register(fd, 0x20) < 0)
    {
        return -1;
    }

    usleep(100);

    if(LCM_write_command(fd, 0x28) < 0) // 4 bit mode, two lines
    {
        return -1;
    }

    usleep(100);

    if(LCM_write_command(fd, 0x06) < 0) // Entry mode set
    {
        return -1;
    }

    usleep(100);

    // if(LCM_write_command(fd, 0x01) < 0) // Clear display
    // {
    //     return -1;
    // }

    // sleep(1);

    if(LCM_write_command(fd, 0x0C) < 0) // Display on, no cursor, no blinking
    {
        return -1;
    }

    sleep(1);

    return 0;
}