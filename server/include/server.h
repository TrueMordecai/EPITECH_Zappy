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
#define MAX_MSG_QUEUE 10

typedef enum orientation {
    NORTH = 0,
    EAST,
    SOUTH,
    WEST
} orientation_t;

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
    uint map_cooldown;
    struct my_client *clients;
} my_server_t;

typedef struct arg_checklist
{
    bool port;
    bool width;
    bool height;
    bool names;
    bool clientsNb;
} arg_checklist_t;

typedef struct inventory {
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
} inv_t;

typedef struct my_client {
    int fd;
    char *team_name;
    uint level;
    uint x;
    uint y;
    orientation_t direction;
    uint food;
    inv_t inventory;
    char **message_queue;
    uint message_queue_size;
    uint cooldown;
    bool dead;
    struct my_client *next;
} my_client_t;

int good_args(int argc, char **argv);
inv_t generate_inventory(void);
inv_t delete_inventory(void);
void server_loop(my_server_t *serv);
void set_arguments(my_server_t *serv, char **argv, int argc);
char *get_client_line(int fd);
my_client_t *make_client(int fd, int x, int y);
void add_client(my_server_t *serv, my_client_t *client);
void decon_client(my_client_t *client);
void del_client(my_server_t *serv, int fd);
void update_clients(my_server_t *serv);
