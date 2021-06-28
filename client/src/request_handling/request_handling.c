#include "request_handling.h"

request 
create_request(request_type req_type)
{
    return (request){req_type};
}