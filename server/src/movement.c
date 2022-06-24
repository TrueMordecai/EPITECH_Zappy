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
        printf("E Going from [%i, %i] dir = %i ", client->x, client->y, client->direction);
        if (client->x == serv->width - 1)
            client->x = 0;
        else
            client->x++;
        printf("to [%i, %i] dir = %i\n", client->x, client->y, client->direction);
    }
    if (client->direction == WEST) {
        printf("W Going from [%i, %i] dir = %i ", client->x, client->y, client->direction);
        if (client->x == 0)
            client->x = serv->width - 1;
        else
            client->x--;
        printf("to [%i, %i] dir = %i\n", client->x, client->y, client->direction);
    }
}

void forward(my_server_t *serv, int fd)
{
    my_client_t *client = get_client_from_fd(serv, fd);

    if (client->direction == NORTH) {
        printf("N Going from [%i, %i] dir = %i ", client->x, client->y, client->direction);
        if (client->y == 0)
            client->y = serv->height - 1;
        else
            client->y--;
        printf("to [%i, %i] dir = %i\n", client->x, client->y, client->direction);
    }
    if (client->direction == SOUTH) {
        printf("S Going from [%i, %i] dir = %i ", client->x, client->y, client->direction);
        if (client->y == serv->height - 1)
            client->y = 0;
        else
            client->y++;
        printf("to [%i, %i] dir = %i\n", client->x, client->y, client->direction);
    }
    forward_aux(serv, fd);
    gui_move_player(serv, client);
    dprintf(fd, "ok\n");
}

void left(my_server_t *serv, int fd)
{
    my_client_t *client = get_client_from_fd(serv, fd);
    printf("Going from [%i, %i] dir = %i ", client->x, client->y, client->direction);
    int dir = client->direction;
    dir -= 1;
    if (dir < 0)
        dir = 3;
    if (dir > 3)
        dir = 0;
    client->direction = dir;
    printf("to [%i, %i] dir = %i\n", client->x, client->y, client->direction);
    gui_rotate_player(serv, client, R_LEFT);
    dprintf(fd, "ok\n");
}

void right(my_server_t *serv, int fd)
{
    my_client_t *client = get_client_from_fd(serv, fd);
    printf("Going from [%i, %i] dir = %i ", client->x, client->y, client->direction);
    int dir = client->direction;
    dir += 1;
    if (dir < 0)
        dir = 3;
    if (dir > 3)
        dir = 0;
    client->direction = dir;
    printf("to [%i, %i] dir = %i\n", client->x, client->y, client->direction);
    gui_rotate_player(serv, client, R_RIGHT);
    dprintf(fd, "ok\n");
}
