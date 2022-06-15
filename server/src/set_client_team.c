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
    printf("Try to this fd %i information\n", client->fd);
    gui_new_player(serv, client);
    dprintf(client->fd, "%d\n", serv->team_sizes[i]);
    dprintf(client->fd, "ppo %d %d\n", client->x, client->y);
}

void set_team(my_client_t *client, char **args, my_server_t *serv)
{
    my_client_t *tmp = serv->clients;
    uint i = 0;

    puts("Set_team");
    for (; tmp; tmp = tmp->next) {
        if (tmp->team_name && !strcmp(tmp->team_name, args[0])) {
            dprintf(client->fd, "TEAM-IN-USE\n");
            del_client(serv, client->fd);
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
    puts("end of Set_team");
}
