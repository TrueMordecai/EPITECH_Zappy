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
#define FOOD 50
#define LINEMATE 30
#define DERAUMERE 15
#define SIBUR 10
#define MENDIANE 10
#define PHIRAS 8
#define THYSTAME 5
#define INCANTATION_TIME 7
#define COMMAND_LIST_SIZE 11

typedef enum orientation {
    NORTH = 0,
    EAST,
    SOUTH,
    WEST
} orientation_t;

typedef enum e_rotation {
    R_LEFT = 0,
    R_RIGHT
} e_rotation_t;


typedef struct my_server {
    uint width;
    uint height;
    char **team_names;
    int *team_sizes;
    uint nb_teams;
    uint clients_nb;
    uint freq;
    int server_fd;
    int gui_fd;
    int port;
    struct protoent *proto;
    struct sockaddr_in address;
    socklen_t addr_len;
    fd_set fds;
    fd_set tmp_fds;
    struct inventory **map;
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

typedef void (*fct_ptr)(struct my_server *, int fd);
typedef fct_ptr (*cmd)();

typedef struct cmd_list {
    char *name;
    uint cd;
    fct_ptr fct;
} cmd_list_t;

typedef struct inventory {
    int food;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
    int player;
} inv_t;

typedef struct my_client {
    int fd;
    char *name;
    char *team_name;
    uint level;
    uint x;
    uint y;
    orientation_t direction;
    uint food;
    inv_t *inventory;
    char **message_queue;
    char *cur;
    uint message_queue_size;
    uint cooldown;
    fct_ptr func;
    bool dead;
    struct my_client *next;
} my_client_t;

int good_args(int argc, char **argv);
inv_t *generate_inventory(void);
void server_loop(my_server_t *serv);
void set_arguments(my_server_t *serv, char **argv, int argc);
char *get_client_line(int fd);
my_client_t *make_client(my_server_t *serv, int fd, int x, int y);
void add_client(my_server_t *serv, my_client_t *client);
void decon_client(my_client_t *client);
void del_client(my_server_t *serv, int fd);
void update_clients(my_server_t *serv);
void update_map(my_server_t *serv);
int check_tile(inv_t tile);
int check_map_full(my_server_t *serv);
int check_tile_ressource(inv_t tile, char ressource);
void update_player_position(my_server_t *serv);
char **str_to_strarr(char *str, char *tok);
void free_strarr(char **arr);
void set_team(my_client_t *client, char **args, my_server_t *serv);
void add_to_queue(char *buf, my_client_t *client);
void check_ritual_level(my_server_t *serv, my_client_t *client, int level);
void check_rit_inv(my_server_t *serv, my_client_t *c, inv_t r, int level);
void ritual_proceed(my_server_t *serv, my_client_t *c, inv_t r, int level);
int get_team_id(my_server_t *serv, char *team);
int check_inc(my_server_t *serv, int fd);
void destroy_egg(my_server_t *serv, my_client_t *egg);

// Client commands
void right(my_server_t *serv, int fd);
void left(my_server_t *serv, int fd);
void forward(my_server_t *serv, int fd);
void broadcast(my_server_t *serv, int fd);
void fork_egg(my_server_t *serv, int fd);
void take(my_server_t *serv, int fd);
void set(my_server_t *serv, int fd);
void look(my_server_t *serv, int fd);
void inventory(my_server_t *serv, int fd);
void incantation(my_server_t *serv, int fd);
void eject(my_server_t *serv, int fd);

// inventory_to_string.c: converts inventory into printable string for look
char *inventory_to_string(inv_t *inv);

// Return a client from its fd
my_client_t *get_client_from_fd(my_server_t *serv, int fd);

// Functiuns related to communication beetween server and GUI client.
void gui_new_player(my_server_t *serv, my_client_t *client);
void gui_move_player(my_server_t *serv, my_client_t *client);
void gui_rotate_player(my_server_t *serv, my_client_t *client, e_rotation_t r);
void gui_set_life_player(my_server_t *serv, my_client_t *client);
void gui_fork_player(my_server_t *serv, my_client_t *client);
void gui_lay_player(my_server_t *serv, my_client_t *client);
void gui_hatch_player(my_server_t *serv, my_client_t *client);
void gui_talk_player(my_server_t *serv, my_client_t *client, char *message);
void gui_spawn_resource(my_server_t *serv, int res, int x, int y);
void gui_remove_resource(my_server_t *serv, int res, int x, int y);
void gui_elevation_player(my_server_t *serv, my_client_t *client);

// Count how many clients are in linked list.
int count_client(my_server_t *serv);

// Connect the gui.
bool connect_gui(my_server_t *serv, char **arr, int fd);

// Debug only
void print_all_clients(my_server_t *serv, char *message);
