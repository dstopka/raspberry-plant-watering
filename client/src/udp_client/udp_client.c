#include <netinet/in.h>
#include <netinet/udp.h>
#include <string.h>
#include <stdio.h>

#include "udp_client.h"

int 
create_socket()
{
    int sockfd;

    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket");
    }

    return sockfd;
}

struct sockaddr_in 
make_servaddr(char* ip, int port)
{
    struct sockaddr_in servaddr;

    memset(&servaddr, 0, sizeof(struct sockaddr_in));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(ip);
    servaddr.sin_port = htons(port);

    return servaddr;
}