/*
** EPITECH PROJECT, 2022
** B-YEP-410-NAN-4-1-zappy-emile.ettel
** File description:
** client_init
*/

#include "server.h"

void add_client(my_server_t *serv, my_client_t *client)
{
    my_client_t *tail = serv->clients;

    client->next = NULL;
    if (serv->clients == NULL) {
        serv->clients = client;
        return;
    }
    while (tail->next)
        tail = tail->next;
    tail->next = client;
}

void del_client(my_server_t *serv, int fd)
{
    my_client_t *tmp = serv->clients;
    my_client_t *rem = NULL;

    if (serv->clients->fd == fd) {
        rem = serv->clients;
        serv->clients = serv->clients->next;
        decon_client(rem);
        return;
    }
    if (serv->clients == NULL)
        return;
    for (; tmp->next && tmp->next->fd != fd; tmp = tmp->next);
    if (tmp->next == NULL)
        return;
    rem = tmp->next;
    tmp->next = tmp->next->next;
    decon_client(rem);
}

void decon_client(my_client_t *client)
{
    if (client->fd != -1)
        close(client->fd);
    if (client->team_name)
        free(client->team_name);
    for (uint i = 0; i < client->message_queue_size; i++)
        free(client->message_queue[i]);
    free(client->message_queue);
    free(client);
}

my_client_t *make_client(int fd, int x, int y)
{
    my_client_t *client = malloc(sizeof(my_client_t));

    client->fd = fd;
    client->team_name = NULL;
    client->level = 1;
    client->x = rand() % x;
    client->y = rand() % y;
    client->direction = rand() % 4;
    client->inventory = generate_inventory();
    client->food = 1260;
    client->cooldown = 0;
    client->message_queue = malloc(sizeof(char*) * 11);
    client->message_queue_size = 0;
    client->next = NULL;
    client->dead = false;
    client->func = NULL;
    dprintf(fd, "WELCOME\n");
    return client;
}