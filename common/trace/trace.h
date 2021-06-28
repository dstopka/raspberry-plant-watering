#ifndef _TRACE_H_
#define _TRACE_H_

#include <stdio.h>

#define TRACE(level, format, msg_args ...) { printf("[%s][%s:%s:%d] ", level, __FILE__, __func__, __LINE__); \
    print_formatted(format, ##msg_args); \
    printf("\n"); \
}

#ifdef DEBUG
#define TRACE_CHECK_DEBUG(args ...) TRACE(LEVEL_DEBUG, args)
#else
#define TRACE_CHECK_DEBUG(args ...) do { } while(0)
#endif

#define LEVEL_DEBUG "DEBUG"
#define LEVEL_ERROR "ERROR"
#define LEVEL_INFO "INFO"
#define LEVEL_WARNING "WARNING"

#define TRACE_DEBUG(...) TRACE_CHECK_DEBUG(__VA_ARGS__)
#define TRACE_ERROR(...) TRACE(LEVEL_ERROR, __VA_ARGS__)
#define TRACE_INFO(...) TRACE(LEVEL_INFO, __VA_ARGS__)
#define TRACE_WARNING(...) TRACE(LEVEL_WARNING, __VA_ARGS__)

void print_formatted(const char* fmt, ...);

#endif