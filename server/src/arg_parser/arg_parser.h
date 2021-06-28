#ifndef _ARG_PARSER_H_
#define _ARG_PARSER_H_

#define CLI_HELP "Usage: %s [-i <ip> -p <port> | -h]\n\n\
OPTIONS AND ARGUMENTS:\n\
-i\t: sets ip address\n\
-p\t: sets port\n\
-h\t: print help and exit\n"

typedef struct arguments
{
    char* ip;
    unsigned int port;
} arguments;

void parse_arguments(arguments* args, int argc, char** argv);

#endif