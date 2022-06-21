/*
** EPITECH PROJECT, 2022
** B-YEP-410-NAN-4-1-zappy-emile.ettel
** File description:
** zappy_look
*/

#include "server.h"

inv_t *get_tile_pos(my_server_t *serv, int x, int y)
{
    if (x < 0)
        x += serv->width;
    if (y < 0)
        y += serv->height;
    return serv->map[y % serv->height][x % serv->width];
}

inv_t *get_next_tile(my_server_t *s, my_client_t *c, int x, int y)
{
    if (c->direction == NORTH)
        return get_tile_pos(s, c->x + x, c->y - y);
    if (c->direction == SOUTH)
        return get_tile_pos(s, c->x - x, c->y + y);
    if (c->direction == WEST)
        return get_tile_pos(s, c->x - y, c->y - x);
    if (c->direction == EAST)
        return get_tile_pos(s, c->x + y, c->y + x);
    return NULL;
}

void look(my_server_t *serv, int fd)
{
    my_client_t *cli = get_client_from_fd(serv, fd);
    char buff[2048];
    char *msg = buff;
    char *tmp;
    inv_t *tile;

    msg += sprintf(msg, "[ ");
    for (int n = 0; n <= cli->level; n++) {
        for (int y = 0; y < (2 * n) + 1; y++) {
            tile = get_next_tile(serv, cli, y - n, n);
            tmp = inventory_to_string(tile);
            msg += sprintf(msg, "%s,", tmp);
            free(tmp);
        }
    }
    msg += sprintf(msg, "]\n");
    dprintf(cli->fd, "%s", buff);
}
