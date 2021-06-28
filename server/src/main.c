
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>

#include "lcd.h"
#include "trace.h"
#include "udp_server.h"
#include "request.h"
#include "response.h"
#include "request_handling.h"
#include "valve_control.h"
#include "arg_parser.h"
#include "i2c_helpers.h"
#include "gpio_helpers.h"
#include "pump_control.h"
#include "print_lcd.h"
#include "humidity_sensor.h"

int main(int argc, char **argv)
{
    arguments args;
    parse_arguments(&args, argc, argv);
    int sockfd = create_bind_socket(args.ip, args.port);
    init_gpio();
    init_valve_control();
    init_pump_control();
    int i2c_fd = open_i2c();
    init_humidity_sensor(i2c_fd);
    init_lcd(i2c_fd);

    request req;
    free(args.ip);
    request_handler handler = make_request_handler();

    while (1)
    {
        struct sockaddr_in cliaddr;
        memset(&cliaddr, 0, sizeof(cliaddr));
        unsigned int len = sizeof(cliaddr);
        recvfrom(sockfd, &req, sizeof(request), MSG_WAITALL, (struct sockaddr *)&cliaddr, &len);
        TRACE_INFO("REQUEST TYPE %d", req.type);
        response resp = handle_request(handler, req, i2c_fd);
        sendto(sockfd, &resp, sizeof(response), MSG_WAITALL, (const struct sockaddr *)&cliaddr, len);
        TRACE_INFO("RESP SENT {type = %d, hum = %.2f, pow = %.2f, state = %d}", resp.type, resp.humidity, resp.power, resp.v_state);
        update_lcd(i2c_fd);
    }

    close(i2c_fd);

    return 0;

    // TODO on exit close
}