/*
** EPITECH PROJECT, 2022
** B-YEP-410-NAN-4-1-zappy-emile.ettel
** File description:
** lay_egg
*/

#include "server.h"

void destroy_egg(my_server_t *serv, my_client_t *egg)
{
    egg->dead = true;
}

void hatch(my_server_t *serv, int fd)
{
    my_client_t *client = get_client_from_fd(serv, fd);

    client->level = 1;
}

void fork_egg(my_server_t *serv, int fd)
{
    my_client_t *dad = get_client_from_fd(serv, fd);
    my_client_t *egg;
    int team_id = get_team_id(serv, dad->team_name);

    if (serv->team_sizes[team_id] <= 0) {
        dprintf(fd, "ko\n");
        return;
    }
    egg = make_client(serv, -2, serv->width, serv->height);
    egg->direction = rand()%4;
    egg->team_name = strdup(dad->team_name);
    egg->level = 0;
    egg->x = dad->x;
    egg->y = dad->y;
    egg->cur = strdup("hatch");
    egg->func = hatch;
    egg->cooldown = 600;
    serv->team_sizes[team_id]--;
    dprintf(fd, "ok\n");
    add_client(serv, egg);
}
