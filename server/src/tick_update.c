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
    {"Look", 7, &look},
    {"Inventory", 1, &inventory},
    {"Broadcast", 7, &broadcast},
    {"Fork", 42, &fork_egg},
    {"Set", 7, &set},
    {"Take", 7, &take},
    {"Incantation", 300, &incantation}
};

fct_ptr get_cmd(char *str)
{
    for (int i = 0; i < COMMAND_LIST_SIZE; i++) {
        if (strncmp(cmd_list[i].name, str, strlen(cmd_list[i].name)) == 0)
            return cmd_list[i].fct;
    }
    return NULL;
}

int get_cd(char *str)
{
    for (int i = 0; i < COMMAND_LIST_SIZE; i++) {
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
    client->message_queue[MAX_MSG_QUEUE - 1] = NULL;
    if (str)
        free(str);
    client->message_queue_size--;
}

void get_next_cmd(my_server_t *serv, my_client_t *client)
{
    fct_ptr tmp = NULL;

    client->func = NULL;
    if (client->message_queue_size == 0)
        return;
    while (client->message_queue[0]) {
        if (get_cmd(client->message_queue[0]) != incantation &&
            !check_inc(serv, client->fd))
            advance_message_queue(client);
        if (get_cmd(client->message_queue[0]) != NULL) {
            tmp = get_cmd(client->message_queue[0]);
            client->cooldown = get_cd(client->message_queue[0]);
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
    if (client->team_name == NULL)
        update_client(serv, client->next);
    if (client->cooldown == 0) {
        if (client->func && client->func != &incantation)
            client->func(serv, client->fd);
        get_next_cmd(serv, client);
    }
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

    for (my_client_t *cli = serv->clients; cli; cli = cli->next)
        if (cli->cooldown > 0)
            cli->cooldown--;
    for (my_client_t *cli = serv->clients; cli; cli = cli->next)
        if (cli->func == &incantation)
            cli->func(serv, cli->fd);
    update_client(serv, serv->clients);
    for (; client; client = client->next)
        if (client->dead) {
            serv->team_sizes[get_team_id(serv, client->team_name)]++;
            del_client(serv, client->fd);
        }
}
