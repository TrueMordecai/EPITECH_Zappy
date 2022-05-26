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

    if (serv->clients == NULL) {
        serv->clients = client;
        return;
    }
    while (tail->next)
        tail = tail->next;
    tail->next = client;
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
    write(fd, "WELCOME\n", 8);
    return client;
}