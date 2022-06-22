/*
** EPITECH PROJECT, 2022
** B-YEP-410-NAN-4-1-zappy-emile.ettel
** File description:
** spawn_ressource
*/

#include "server.h"

void gui_spawn_resource(my_server_t *serv, int res, int x, int y)
{
    if (serv->gui_fd == -1)
        return;
    printf("map spawn %i %i %i\n", res, x, y);
    dprintf(serv->gui_fd, "map spawn %i %i %i\n", res, x, y);
}
