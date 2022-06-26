/*
** EPITECH PROJECT, 2022
** B-YEP-410-NAN-4-1-zappy-emile.ettel
** File description:
** broadcast
*/

#include "server.h"

int get_shortest(int pos1, int pos2, int max)
{
    int ret;

    if (abs(pos2 - pos1) < abs(max - pos2 + pos1))
        ret = pos2 - pos1;
    else
        ret = -1 * (max - pos2 + pos1);
    return ret;
}

int add_shimmy(int cur, int max, int min, int path[2])
{
    int shortest = 0;
    int furthest = 0;
    int vert = 0;
    int add = 0;

    if (abs(path[0]) > abs(path[1])) {
        vert = 1;
        shortest = path[1];
        furthest = path[0];
    } else {
        vert = 0;
        shortest = path[0];
        furthest = path[1];
    }
    add = get_add(vert, furthest, shortest);
    if (cur + add < min)
        return max + (add + 1);
    return cur + add;
}

int get_case(orientation_t dir, int path[2])
{
    int furthest = 0;
    int cur = 1;
    int base[2] = {0, 0};
    int ret = 1;

    if (path[0] == 0 && path[1] == 0)
        return 0;
    if (abs(path[0]) > abs(path[1])) {
        furthest = path[0];
        base[0] = get_base_x(dir, furthest);
    } else {
        furthest = path[1];
        base[0] = get_base_y(dir, furthest);
    }
    (base[0] == 3) ? (base[1] = 2) : (0);
    (base[0] == 5) ? (base[1] = 4) : (0);
    (base[0] == 7) ? (base[1] = 6) : (0);
    for (;cur != abs(furthest); cur++)
        ret = (1 + cur * 2) * (1 + cur * 2);
    return add_shimmy(ret + (base[1] * cur), (1+cur*2)*(1+cur*2), ret, path);
}

void send_message(my_server_t *serv, char *msg, int x, int y)
{
    my_client_t *client = serv->clients;
    int path[2];

    while (client) {
        if (client->team_name && client->fd > 0) {
            path[0] = get_shortest(x, client->x, serv->width);
            path[1] = get_shortest(y, client->y, serv->height);
            dprintf(client->fd, "pbc %d %s\n",
            get_case(client->direction, path), msg);
        }
        client = client->next;
    }
}

void broadcast(my_server_t *serv, int fd)
{
    my_client_t *client = get_client_from_fd(serv, fd);
    char **cmd = str_to_strarr(client->cur, " \n\r\t");

    if (cmd[1] == NULL) {
        dprintf(fd, "ok\n");
        return;
    }
    send_message(serv, cmd[1], client->x, client->y);
    dprintf(fd, "ok\n");
}
