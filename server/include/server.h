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

#define MAX_NAME_LENGTH        32
#define MAX_DESCRIPTION_LENGTH 255
#define MAX_BODY_LENGTH        512
#define MAX_MSG_LENGTH         (MAX_NAME_LENGTH + MAX_DESCRIPTION_LENGTH + \
                                 MAX_BODY_LENGTH + 20)

typedef struct my_server {
    uint width;
    uint height;
    char *team_names;
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