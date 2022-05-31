/*
** EPITECH PROJECT, 2022
** B-YEP-410-NAN-4-1-zappy-emile.ettel
** File description:
** tick_update
*/

#include "server.h"

void update_client(my_client_t *client)
{
    if (!client)
        return;
    if (client->cooldown == 0) {

    }
    if (client->cooldown > 0)
        client->cooldown--;
    if (client->food == 0) {
        dprintf(client->fd, "%s\n", "dead");
        client->dead = true;
    }
    else
        client->food--;
    update_client(client->next);
}

void update_clients(my_server_t *serv)
{
    my_client_t *client = serv->clients;

    update_client(serv->clients);
    for (; client; client = client->next)
        if (client->dead) {
            printf("Client %d has died, disconnecting\n", client->fd);
            del_client(serv, client->fd);
        }
}