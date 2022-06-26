/*
** EPITECH PROJECT, 2022
** B-YEP-410-NAN-4-1-zappy-emile.ettel
** File description:
** check_win
*/

#include "server.h"

int check_team_win(my_server_t *serv, char *team)
{
    my_client_t *client = serv->clients;
    int clients = 0;

    while (client) {
        if (client->level == 8 && !strcmp(team, client->team_name))
            clients++;
        client = client->next;
    }
    if (clients >= 6)
        return 1;
    return 0;
}

void check_win(my_server_t *serv)
{
    for (uint i = 0; i < serv->nb_teams; i++) {
        if (check_team_win(serv, serv->team_names[i])) {
            printf("%s has won!\nServer closing\n", serv->team_names[i]);
            serv->win = true;
            return;
        }
    }
}
