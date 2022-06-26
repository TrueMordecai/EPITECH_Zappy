/*
** EPITECH PROJECT, 2022
** B-YEP-410-NAN-4-1-zappy-emile.ettel
** File description:
** movement
*/

#include "server.h"

static void forward_aux(my_server_t *serv, int fd)
{
    my_client_t *c = get_client_from_fd(serv, fd);

    if (c->direction == EAST) {
        printf("E Going from [%i, %i] dir = %i ", c->x, c->y, c->direction);
        if (c->x == serv->width - 1)
            c->x = 0;
        else
            c->x++;
        printf("to [%i, %i] dir = %i\n", c->x, c->y, c->direction);
    }
    if (c->direction == WEST) {
        printf("W Going from [%i, %i] dir = %i ", c->x, c->y, c->direction);
        if (c->x == 0)
            c->x = serv->width - 1;
        else
            c->x--;
        printf("to [%i, %i] dir = %i\n", c->x, c->y, c->direction);
    }
}

void forward(my_server_t *serv, int fd)
{
    my_client_t *c = get_client_from_fd(serv, fd);

    if (c->direction == NORTH) {
        printf("N Going from [%i, %i] dir = %i ", c->x, c->y, c->direction);
        if (c->y == 0)
            c->y = serv->height - 1;
        else
            c->y--;
        printf("to [%i, %i] dir = %i\n", c->x, c->y, c->direction);
    }
    if (c->direction == SOUTH) {
        printf("S Going from [%i, %i] dir = %i ", c->x, c->y, c->direction);
        if (c->y == serv->height - 1)
            c->y = 0;
        else
            c->y++;
        printf("to [%i, %i] dir = %i\n", c->x, c->y, c->direction);
    }
    forward_aux(serv, fd);
    gui_move_player(serv, c);
    dprintf(fd, "ok\n");
}

void left(my_server_t *serv, int fd)
{
    my_client_t *c = get_client_from_fd(serv, fd);
    printf("Going from [%i, %i] dir = %i ", c->x, c->y, c->direction);
    int dir = c->direction;
    dir -= 1;
    if (dir < 0)
        dir = 3;
    if (dir > 3)
        dir = 0;
    c->direction = dir;
    printf("to [%i, %i] dir = %i\n", c->x, c->y, c->direction);
    gui_rotate_player(serv, c, R_LEFT);
    dprintf(fd, "ok\n");
}

void right(my_server_t *serv, int fd)
{
    my_client_t *c = get_client_from_fd(serv, fd);
    printf("Going from [%i, %i] dir = %i ", c->x, c->y, c->direction);
    int dir = c->direction;
    dir += 1;
    if (dir < 0)
        dir = 3;
    if (dir > 3)
        dir = 0;
    c->direction = dir;
    printf("to [%i, %i] dir = %i\n", c->x, c->y, c->direction);
    gui_rotate_player(serv, c, R_RIGHT);
    dprintf(fd, "ok\n");
}
