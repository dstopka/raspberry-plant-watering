#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#include "arg_parser.h"
#include "trace.h"

static int is_valid_ip(char* ip);

void
parse_arguments(arguments* args, int argc, char** argv)
{
    int opt;
	while((opt = getopt(argc, argv, "i:p:h")) != -1)
	{
        char* p;
		switch(opt)
		{			
            case 'i':
                if(is_valid_ip(optarg) < 0)
                {
                    printf("%s is not a valid IPv4 address. Exiting...\n", optarg);
                    _exit(EXIT_FAILURE);
                }

                args->ip = (char*)malloc(strlen(optarg) * sizeof(char));
                if(args->ip == NULL)
                {
                    TRACE_ERROR("Out of memory");
                    _exit(EXIT_FAILURE);
                }
                strcpy(args->ip, optarg);
                break;
            case 'p':
                args->port = strtol(optarg, &p, 10);    
                if(*p != '\0')
                {
                    printf("Port argument must be an integer. Exiting...\n");
                    _exit(EXIT_FAILURE);
                }
                break;
            case 'h':
                printf(CLI_HELP, argv[0]);
                _exit(EXIT_SUCCESS);
                break;
			default: 
				printf("Wrong argument passed.\nTry %s -h for details.\n", argv[0]);
				_exit(EXIT_FAILURE);
		}
	}
    if(optind != argc || argc != 5)
    {
        printf("Wrong number of arguments.\nTry %s -h for details.\n", argv[0]);
        _exit(EXIT_FAILURE);
    }
}

int
is_valid_ip(char* ip)
{
    TRACE_DEBUG("Checking validity of %s IPv4\n", ip);
    struct sockaddr_in sa;
    int rc = inet_pton(AF_INET, ip, &(sa.sin_addr));

    return rc == 1 ? 0 : -1;
}