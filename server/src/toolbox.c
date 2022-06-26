/*
** EPITECH PROJECT, 2022
** B-YEP-410-NAN-4-1-zappy-emile.ettel
** File description:
** toolbox
*/

#include "server.h"

my_client_t *get_client_from_fd(my_server_t *serv, int fd)
{
    my_client_t *cur = serv->clients;

    if (fd == -1)
        return (NULL);
    if (!serv->clients)
        return (NULL);
    if (cur->fd == fd)
        return (cur);
    while (cur) {
        if (cur->fd == fd)
            return (cur);
        cur = cur->next;
    }
    return (NULL);
}

int count_client(my_server_t *serv)
{
    int res = 0;

    my_client_t *cur = serv->clients;
    if (!cur)
        return 0;
    while (cur->next) {
        cur = cur->next;
        res++;
    }
    return res;
}

int egg_presence(inv_t *inv)
{
    if (inv->egg > 0) {
        inv->egg--;
        return 1;
    }
    return 0;
}

int get_add(int vert, int furthest, int shortest)
{
    int add;

    if (vert == 0) {
        if (furthest > 0)
            add = -1 * shortest;
        else
            add = shortest;
    }
    if (vert == 1) {
        if (furthest > 0)
            add = shortest;
        else
            add = -1 * shortest;
    }
    return add;
}

int get_team_id(my_server_t *serv, char *team)
{
    uint i = 0;

    for (; i < serv->nb_teams; i++)
        if (!strcmp(serv->team_names[i], team))
            return i;
    return -1;
}
