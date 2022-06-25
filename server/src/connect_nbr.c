/*
** EPITECH PROJECT, 2022
** B-YEP-410-NAN-4-1-zappy-emile.ettel
** File description:
** connect_nbr
*/

#include "server.h"

void connect_nbr(my_server_t *serv, int fd)
{
    my_client_t *client = get_client_from_fd(serv, fd);
    int team_id = get_team_id(serv, client->team_name);

    dprintf(fd, "%d\n", serv->team_sizes[team_id]);
}
