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
    x %= serv->width;
    y %= serv->height;
    return &serv->map[y][x];
}

inv_t *get_next_tile(my_server_t *s, my_client_t *c, int x, int y)
{
    if (c->direction == NORTH)
        return get_tile_pos(s, c->x + x, c->y - y);
    if (c->direction == SOUTH)
        return get_tile_pos(s, c->x - x, c->y + y);
    if (c->direction == EAST)
        return get_tile_pos(s, c->x + y, c->y + x);
    if (c->direction == WEST)
        return get_tile_pos(s, c->x - y, c->y - x);
    return &s->map[0][0];
}

void look(my_server_t *serv, int fd)
{
    my_client_t *cli = get_client_from_fd(serv, fd);
    char buff[2048];
    char *msg = buff;
    char *tmp;
    inv_t *tile;

    strcpy(msg, "[");
    for (uint n = 0; n <= cli->level; n++) {
        for (uint y = 0; y < (2 * n) + 1; y++) {
            tile = get_next_tile(serv, cli, y - n, n);
            tmp = inventory_to_string(tile);
            strcat(msg, tmp);
            if (y < (2 * n) || n + 1 <= cli->level) {
                strcat(msg, ",");
            }
            free(tmp);
        }
    }
    dprintf(cli->fd, "%s]\n", buff);
}
