#ifndef _UDP_CLIENT_H_
#define _UDP_CLIENT_H_

#include <arpa/inet.h>

int create_socket();
struct sockaddr_in make_servaddr(char* ip, int port);

#endif