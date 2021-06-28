#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <arpa/inet.h>

#include "request.h"
#include "response.h"
#include "request_handling.h"
#include "udp_client.h"
#include "window.h"
#include "print_screen.h"
#include "response_handling.h"
#include "trace.h"

int main(/* argc, argv[] */)
{
   // TRACE_DEBUG("JOLJOL");
   WINDOW *window = init_window();
   int sockfd = create_socket();
   struct sockaddr_in servaddr = make_servaddr("192.168.0.194", 5050);

   response_handler handler;
   handler.get_humidity_handler = &print_humidity;
   handler.trigger_valve_handler = &print_valve_state;
   handler.pump_action_handler = &print_pump_power;

   request req = create_request(GET_HUMIDITY);
   unsigned int len = sizeof(servaddr);
   sendto(sockfd, &req, sizeof(request), MSG_CONFIRM,
          (const struct sockaddr *)&servaddr, len);
   response resp;
   recvfrom(sockfd, &resp, sizeof(response), MSG_WAITALL, NULL, 0);
   handle_response(handler, resp, window);

   req = create_request(GET_VALVE_STATE);
   sendto(sockfd, &req, sizeof(request), MSG_CONFIRM,
          (const struct sockaddr *)&servaddr, len);
   recvfrom(sockfd, &resp, sizeof(response), MSG_WAITALL, NULL, 0);
   handle_response(handler, resp, window);

   wrefresh(window);

   int key;
   char actions[][15] = {"Get humidity", "Trigger valve", "Pump +", "Pump -"};
   request_type action_vals[] = {GET_HUMIDITY, TRIGGER_VALVE, PUMP_UP, PUMP_DOWN};

   int actions_size = (int)(sizeof(actions) / sizeof(actions[0]));

   for (int i = 0; i < actions_size; ++i)
   {
      if (i == 0)
      {
         wattron(window, A_STANDOUT);
      } 
      else
      {
         wattroff(window, A_STANDOUT);
      }
      mvwprintw(window, i + 1, (int)(COLS / 2), "%s", actions[i]);
   }

   wrefresh(window);

   int index = 0;
   while ((key = wgetch(window)) != 27)
   {
      mvwprintw(window, index + 1, (int)(COLS / 2), "%s", actions[index]);
      switch (key)
      {
      case KEY_UP:
         index = (--index < 0) ? actions_size - 1 : index;
         break;
      case KEY_DOWN:
         index = (++index > actions_size - 1) ? 0 : index;
         break;
      case 10:
      {
         req = create_request(action_vals[index]);
         sendto(sockfd, &req, sizeof(request), MSG_CONFIRM,
                (const struct sockaddr *)&servaddr, len);
         recvfrom(sockfd, &resp, sizeof(response), MSG_WAITALL, NULL, 0);
         handle_response(handler, resp, window);
         break;
      }
      default:
         break;
      }

      wattron(window, A_STANDOUT);
      mvwprintw(window, index + 1, (int)(COLS / 2), "%s", actions[index]);
      wattroff(window, A_STANDOUT);
   }

   return 0;
}
