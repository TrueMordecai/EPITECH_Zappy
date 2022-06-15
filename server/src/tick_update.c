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
    {"Left", 7, &left},
    {"Broadcast", 7, &broadcast}
};

fct_ptr get_cmd(char *str)
{
    for (int i = 0; i < 4; i++) {
        if (strncmp(cmd_list[i].name, str, strlen(cmd_list[i].name)) == 0)
            return cmd_list[i].fct;
    }
    return NULL;
}

int get_cd(char *str)
{
    for (int i = 0; i < 4; i++) {
        if (strncmp(cmd_list[i].name, str, strlen(cmd_list[i].name)) == 0)
            return cmd_list[i].cd;
    }
    return 0;
}

void advance_message_queue(my_client_t *client)
{
    char *str = client->message_queue[0];

    for (int i = 1; i < MAX_MSG_QUEUE; i++) {
        client->message_queue[i - 1] = client->message_queue[i];
    }
    if (str)
        free(str);
    client->message_queue_size--;
}

void get_next_cmd(my_client_t *client)
{
    fct_ptr tmp = NULL;

    client->func = NULL;
    if (client->message_queue_size == 0)
        return;
    while (client->message_queue[0]) {
        if (get_cmd(client->message_queue[0]) != NULL) {
            tmp = get_cmd(client->message_queue[0]);
            client->cooldown = 1 + get_cd(client->message_queue[0]);
            client->func = tmp;
            (client->cur) ? (free(client->cur)) : (0);
            client->cur = NULL;
            client->cur = strdup(client->message_queue[0]);
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
            client->func(serv, client->fd);
        get_next_cmd(client);
    }
    if (client->cooldown > 0)
        client->cooldown--;
    if (client->food == 0) {
        dprintf(client->fd, "dead\n");
        client->dead = true;
    } else {
        client->food--;
        gui_set_life_player(serv, client);
    }
    update_client(serv, client->next);
}

void update_clients(my_server_t *serv)
{
    my_client_t *client = serv->clients;

    update_client(serv, serv->clients);
    for (; client; client = client->next)
        if (client->dead)
            del_client(serv, client->fd);
}