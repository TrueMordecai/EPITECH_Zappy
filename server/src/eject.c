/*
** EPITECH PROJECT, 2022
** B-YEP-410-NAN-4-1-zappy-emile.ettel
** File description:
** eject
*/

#include "server.h"

void disrupt_elevation(my_client_t *victim)
{
    if (!strcmp(victim->cur, "Participant") || victim->func == &incantation) {
        victim->cooldown = 0;
        victim->func = NULL;
    }
}

void push_client(my_server_t *serv, my_client_t *client, my_client_t *victim)
{
    if (client->direction == NORTH) {
        victim->y--;
        dprintf(victim->fd, "eject: N\n");
    }
    if (client->direction == SOUTH) {
        victim->y++;
        dprintf(victim->fd, "eject: S\n");
    }
    if (client->direction == EAST) {
        victim->x++;
        dprintf(victim->fd, "eject: E\n");
    }
    if (client->direction == WEST) {
        victim->x--;
        dprintf(victim->fd, "eject: W\n");
    }
    disrupt_elevation(victim);
    if (victim->level == 0) {
        destroy_egg(serv, victim);
    }
}

void eject(my_server_t *serv, int fd)
{
    my_client_t *client = get_client_from_fd(serv, fd);
    my_client_t *clients = serv->clients;
    int pushed = 0;

    for (; clients; clients = clients->next) {
        if (clients->x == client->x && clients->y && client->y &&
        client->fd != clients->fd) {
            pushed++;
            push_client(serv, client, clients);
        }
    }
    if (pushed > 0)
        dprintf(client->fd, "ok\n");
    else
        dprintf(client->fd, "ko\n");
}
