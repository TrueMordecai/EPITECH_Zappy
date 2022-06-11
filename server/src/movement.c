/*
** EPITECH PROJECT, 2022
** B-YEP-410-NAN-4-1-zappy-emile.ettel
** File description:
** movement
*/

#include "server.h"

static void forward_aux(my_server_t *serv, int fd)
{
    my_client_t *client = get_client_from_fd(serv, fd);
    if (client->direction == EAST) {
        if (client->x == serv->width - 1)
            client->x = 0;
        else
            client->x++;
    }
    if (client->direction == WEST) {
        if (client->x == 0)
            client->x = serv->width - 1;
        else
            client->x--;
    }
}

void forward(my_server_t *serv, int fd)
{
    my_client_t *client = get_client_from_fd(serv, fd);
    if (client->direction == NORTH) {
        if (client->y == 0)
            client->y = serv->height - 1;
        else
            client->y--;
    }
    if (client->direction == SOUTH) {
        if (client->y == serv->height - 1)
            client->y = 0;
        else
            client->y++;
    }
    forward_aux(serv, fd);
    gui_move_player(serv, client);
    dprintf(fd, "ok\n");
}

void left(my_server_t *serv, int fd)
{
    my_client_t *client = get_client_from_fd(serv, fd);
    if (client->direction == NORTH)
        client->direction = WEST;
    if (client->direction == EAST)
        client->direction = NORTH;
    if (client->direction == SOUTH)
        client->direction = EAST;
    if (client->direction == WEST)
        client->direction = SOUTH;
    gui_rotate_player(serv, client, R_LEFT);
    dprintf(fd, "ok\n");
}

void right(my_server_t *serv, int fd)
{
    my_client_t *client = get_client_from_fd(serv, fd);
    if (client->direction == NORTH)
        client->direction = EAST;
    if (client->direction == EAST)
        client->direction = SOUTH;
    if (client->direction == SOUTH)
        client->direction = WEST;
    if (client->direction == WEST)
        client->direction = NORTH;
    dprintf(fd, "ok\n");
}
