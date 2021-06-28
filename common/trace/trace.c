#include <stdarg.h>

#include "trace.h"

void print_formatted(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end (args);
}