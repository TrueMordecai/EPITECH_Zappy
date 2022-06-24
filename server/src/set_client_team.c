/*
** EPITECH PROJECT, 2022
** B-YEP-410-NAN-4-1-zappy-emile.ettel
** File description:
** set_client_team
*/

#include "server.h"

void set_team_aux(my_server_t *serv, int i, my_client_t *client, char **args)
{
    client->team_name = strdup(args[0]);
    serv->team_sizes[i]--;
    gui_new_player(serv, client);
    dprintf(client->fd, "%d\n", serv->team_sizes[i]);
    printf("player pos == %d.%d looking %i\n", client->x, client->y, client->direction);
    dprintf(client->fd, "ppo %d %d %i\n", client->x, client->y, client->direction);
}

void set_egg(my_client_t *client, char **args, my_server_t *serv)
{
    my_client_t *tmp = serv->clients;

    while (tmp != NULL) {
        if (tmp->team_name &&
            !strcmp(tmp->team_name, args[0]) && tmp->fd == -2) {
            tmp->fd = client->fd;
            client->fd = -1;
            del_client(serv, -1);
            dprintf(tmp->fd, "%d\n", serv->team_sizes[get_team_id(serv,
            tmp->team_name)]);
            dprintf(tmp->fd, "ppo %d %d\n", tmp->x, tmp->y);
            return;
        }
        tmp = tmp->next;
    }
    dprintf(client->fd, "TEAM-IN-USE\n");
    del_client(serv, client->fd);
}

void set_team(my_client_t *client, char **args, my_server_t *serv)
{
    my_client_t *tmp = serv->clients;
    uint i = 0;

    for (; tmp; tmp = tmp->next) {
        if (tmp->team_name && !strcmp(tmp->team_name, args[0])) {
            set_egg(client, args, serv);
            return;
        }
    }
    for (; i < serv->nb_teams; i++)
        if (!strcmp(serv->team_names[i], args[0]))
            break;
    if (i == serv->nb_teams) {
        dprintf(client->fd, "TEAM-NOT-FOUND\n");
        del_client(serv, client->fd);
        return;
    }
    set_team_aux(serv, i, client, args);
}
