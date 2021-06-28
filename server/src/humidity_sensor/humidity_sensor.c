#include <math.h>
#include <unistd.h>
#include <errno.h>

#include "humidity_sensor.h"
#include "i2c_helpers.h"
#include "trace.h"

static volatile double humidity = 0;

void measure_humidity(const int fd)
{
    i2c_point_to_addr(fd, SENSOR_ADDR);

    // char config[3] = {0x01, 0x84, 0x83};
    // if (write(fd, config, 3) < 0)
    // {
    //     TRACE_ERROR("Writing to %d failed with code %d", fd, errno);
    // }

    // usleep(10000);

    // char reg[1] = {0x00};
    // if (write(fd, reg, 1) < 0)
    // {
    //     TRACE_ERROR("Writing to %d failed with code %d", fd, errno);
    // }

    // usleep(10000);

    // char val[2];
    // if (read(fd, val, 2) != 2)
    // {
    //     TRACE_ERROR("Error reading from %d", fd);
    // }

    // int humidity = (val[0] << 2) + val[1];

    char config_buff[3] = {0x01, 0xC3, 0x03};
    char val_buff[2] = {0x00, 0x00};

    if(write(fd, config_buff, 3) < 0)
    {
        TRACE_ERROR("Writing to %d failed with code %d", fd, errno);
    }

    while((val_buff[0] & 0x80) == 0) 
    {
        if(read(fd, val_buff, 2) != 2)
        {
            TRACE_ERROR("Error reading from %d", fd);
        }
    }

    config_buff[0] = 0x00;
    if(write(fd, config_buff, 1) < 0)
    {
        TRACE_ERROR("Writing to %d failed with code %d", fd, errno);
    }

    if(read(fd, val_buff, 2) != 2)
    {
        TRACE_ERROR("Error reading from %d", fd);
    }

    int val = val_buff[0] << 8 | val_buff[1];

    humidity = (fabs((float)(DRY_VAL - val) / (float)(DRY_VAL - WET_VAL)) * 100);
    TRACE_INFO("New humidity reading - %.2f%%", humidity);
    // TRACE_INFO("New humidity reading - %d", humidity);
}

void init_humidity_sensor(const int fd)
{
    measure_humidity(fd);
}

double
get_humidity()
{
    return humidity;
}