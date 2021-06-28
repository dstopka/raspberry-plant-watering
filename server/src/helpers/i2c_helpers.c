#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#include "i2c_helpers.h"
#include "trace.h"

void
i2c_point_to_addr(int fd, int addr)
{
    static int current_addr = 0;

    if(current_addr == addr)
    {
        TRACE_DEBUG("i2c already pointing to %02hhx. No action needed.", addr);
        return;
    }

    if(ioctl(fd, I2C_SLAVE, addr) < 0)
    {
        TRACE_ERROR("Ioctl failed. {fd = %d, addr = 0x%02hhx, errno = %d}", fd, addr, errno);
        _exit(EXIT_FAILURE);
    }

    current_addr = addr;
    TRACE_DEBUG("i2c pointing to %02hhx", addr);
}

int
open_i2c()
{
    const char* path = "/dev/i2c-1";
    int fd = open(path, O_RDWR);
    if(fd < 0)
    {
        TRACE_ERROR("Opening %s failed", path);
        _exit(EXIT_FAILURE);
    }

    TRACE_INFO("Opening %s - success", path);

    return fd;
}