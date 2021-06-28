#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "trace.h"
#include "udp_server.h"

static void bind_socket(int sockfd, char* ip, unsigned int port);

int
create_bind_socket(char* ip, unsigned int port)
{
    int sockfd;

    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        TRACE_ERROR("Creating socket failed. Errno = %d", errno);
        _exit(EXIT_FAILURE);
    }

    bind_socket(sockfd, ip, port);

    return sockfd;
}

void
bind_socket(int sockfd, char* ip, unsigned int port)
{
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(ip); //"192.168.0.194"
    servaddr.sin_port = htons(port);

    if(bind(sockfd, (const struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
    {
       TRACE_ERROR("Binding socket to %s:%d failed. Errno = %d", ip, port, errno);
        _exit(EXIT_FAILURE);
    } 
    else 
    {
        TRACE_INFO("Socket successfully bind to %s:%d", ip, port);
    }
}