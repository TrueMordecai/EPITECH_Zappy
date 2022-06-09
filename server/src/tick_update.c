/*
** EPITECH PROJECT, 2022
** B-YEP-410-NAN-4-1-zappy-emile.ettel
** File description:
** tick_update
*/

#include "server.h"

const cmd_list_t cmd_list[] = {
    {"Forward", 7, &forward},
    {"Right", 7, &right},
    {"Left", 7, &left}
};

fct_ptr get_cmd(char *str)
{
    for (int i = 0; i < 3; i++) {
        if (strcmp(cmd_list[i].name, str) == 0)
            return cmd_list[i].fct;
    }
    return NULL;
}

int get_cd(char *str)
{
    for (int i = 0; i < 3; i++) {
        if (strcmp(cmd_list[i].name, str) == 0)
            return cmd_list[i].cd;
    }
    return 0;
}

void advance_message_queue(my_client_t *client)
{
    char *str = client->message_queue[0];

    for (int i = 1; i < MAX_MSG_QUEUE; i++)
        client->message_queue[i - 1] = client->message_queue[i];
    if (str)
        free(str);
}

fct_ptr get_next_cmd(my_client_t *client)
{
    fct_ptr tmp = NULL;

    if (client->message_queue_size == 0)
        return NULL;
    while (client->message_queue[0]) {
        if (get_cmd(client->message_queue[0]) != NULL) {
            tmp = get_cmd(client->message_queue[0]);
            client->cooldown = 1 + get_cd(client->message_queue[0]);
            client->func = tmp;
            advance_message_queue(client);
            break;
        }
        advance_message_queue(client);
    }
}

void update_client(my_server_t *serv, my_client_t *client)
{
    if (!client)
        return;
    if (client->cooldown == 0) {
        if (client->func)
            client->func(serv, client);
        get_next_cmd(client);
    }
    if (client->cooldown > 0)
        client->cooldown--;
    if (client->food == 0) {
        dprintf(client->fd, "%s\n", "dead");
        client->dead = true;
    }
    else
        client->food--;
    update_client(serv, client->next);
}

void update_clients(my_server_t *serv)
{
    my_client_t *client = serv->clients;

    update_client(serv, serv->clients);
    for (; client; client = client->next)
        if (client->dead) {
            printf("Client %d has died, disconnecting\n", client->fd);
            del_client(serv, client->fd);
        }
}