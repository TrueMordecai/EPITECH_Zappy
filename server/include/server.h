/*
** EPITECH PROJECT, 2022
** B-YEP-400-NAN-4-1-zappy-emile.ettel
** File description:
** server
*/

#pragma once

#include <arpa/inet.h>
#include <ctype.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <uuid/uuid.h>

#define USAGE_MSG "USAGE: ./zappy_server -p port -x width -y height -n name1 \
name2 ... -c clientsNb\n\
-f freq\n\
\tport\t\t is the port number\n\
\twidth\t\t is the width of the world\n\
\theight\t\t is the height of the world\n\
\tnameX\t\t is the name of the team X\n\
\tclientsNb\t is the number of authorized clients per team\n\
\tfreq\t\t is the reciprocal of time unit for execution of actions\n"

#define MAX_NAME_LENGTH        32
#define MAX_DESCRIPTION_LENGTH 255
#define MAX_BODY_LENGTH        512
#define MAX_MSG_LENGTH         (MAX_NAME_LENGTH + MAX_DESCRIPTION_LENGTH + \
                                 MAX_BODY_LENGTH + 20)

typedef struct my_server {
    uint width;
    uint height;
    char **team_names;
    uint nb_teams;
    uint clients_nb;
    uint freq;
    int server_fd;
    int port;
    struct protoent *proto;
    struct sockaddr_in address;
    socklen_t addr_len;
    fd_set fds;
    fd_set tmp_fds;
} my_server_t;

typedef struct arg_checklist
{
    bool port;
    bool width;
    bool height;
    bool names;
    bool clientsNb;
} arg_checklist_t;

int good_args(int argc, char **argv);
void server_loop(my_server_t *serv);
void set_arguments(my_server_t *serv, char **argv, int argc);