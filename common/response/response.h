#ifndef _RESPONSE_H_
#define _RESPONSE_H_

#include "request.h"
#include "valve_state.h"

typedef struct response {
    request_type type;
    union {
        double humidity;
        double power;
        valve_state v_state;
    };
} response;

#endif