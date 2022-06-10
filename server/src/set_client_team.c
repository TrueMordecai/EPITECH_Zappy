/*
** EPITECH PROJECT, 2022
** B-YEP-410-NAN-4-1-zappy-emile.ettel
** File description:
** set_client_team
*/

#include "server.h"

void set_team(my_client_t *client, char **args, my_server_t *serv)
{
    my_client_t *tmp = serv->clients;
    uint i = 0;

    if (args[1]) {
        serv->gui_fd = client->fd;
        client->fd = -1;
        del_client(serv, -1);
        dprintf(serv->gui_fd, "map_size=%i,%i", serv->width, serv->height);
        return;
    }
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
    client->team_name = strdup(args[0]);
    serv->team_sizes[i]--;
    gui_new_player(client->fd, serv);
    dprintf(client->fd, "%d\n", serv->team_sizes[i]);
    dprintf(client->fd, "%d %d\n", client->x, client->y);
}
