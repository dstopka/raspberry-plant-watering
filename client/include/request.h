#ifndef _REQUEST_H_
#define _REQUEST_H_

typedef enum request_type {
    GET_HUMIDITY,
    TRIGGER_VALVE,
    GET_VALVE_STATE,
    PUMP_UP,
    PUMP_DOWN,
    GET_PUMP_POWER
} request_type;

typedef struct request
{
    request_type type;
} request;

// char* request_type_string(request_type type);

#endif