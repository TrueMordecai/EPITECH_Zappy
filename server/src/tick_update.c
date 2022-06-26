/*
** EPITECH PROJECT, 2022
** B-YEP-410-NAN-4-1-zappy-emile.ettel
** File description:
** tick_update
*/

#include "server.h"

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

void set_func(my_client_t *cli)
{
    cli->cooldown = get_cd(cli->message_queue[0]);
    cli->func = get_cmd(cli->message_queue[0]);
    (cli->cur) ? (free(cli->cur)) : (0);
    cli->cur = NULL;
    cli->cur = strdup(cli->message_queue[0]);
    printf("Info :: [%i, %i] dir = %i\n", cli->x, cli->y, cli->direction);
    advance_message_queue(cli);
}

void get_next_cmd(my_server_t *serv, my_client_t *client)
{
    while (client->message_queue[0]) {
        if (get_cmd(client->message_queue[0]) == incantation &&
        check_inc(serv, client->fd)) {
            advance_message_queue(client);
            break;
        }
        if (get_cmd(client->message_queue[0]) == connect_nbr) {
            connect_nbr(serv, client->fd);
            advance_message_queue(client);
            continue;
        }
        if (get_cmd(client->message_queue[0]) != NULL &&
        get_cmd(client->message_queue[0]) != incantation) {
            set_func(client);
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
        if (client->func && client->func != &incantation) {
            client->func(serv, client->fd);
            client->func = NULL;
        }
        if (client->message_queue_size > 0)
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
        if (cli->func == &incantation && cli->cooldown == 0) {
            cli->func(serv, cli->fd);
            cli->func = NULL;
        }
    update_client(serv, serv->clients);
    for (; client; client = client->next)
        if (client->dead) {
            serv->team_sizes[get_team_id(serv, client->team_name)]++;
            del_client(serv, client->fd);
        }
    check_win(serv);
}
