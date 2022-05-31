/*
** EPITECH PROJECT, 2022
** B-YEP-410-NAN-4-1-zappy-emile.ettel
** File description:
** map_info
*/

#include "server.h"

int check_tile(inv_t tile)
{
    int ret = 0;

    if (tile.food || tile.deraumere || tile.linemate || tile.sibur ||
        tile.mendiane || tile.phiras || tile.thystame)
        ret = 1;
    return ret;
}

int check_tile_ressource(inv_t tile, char ressource)
{
    int ret = 0;

    if (ressource == 'f' && tile.food)
        ret = 1;
    if (ressource == 'd' && tile.deraumere)
        ret = 1;
    if (ressource == 'l' && tile.linemate)
        ret = 1;
    if (ressource == 's' && tile.sibur)
        ret = 1;
    if (ressource == 'm' && tile.mendiane)
        ret = 1;
    if (ressource == 'p' && tile.phiras)
        ret = 1;
    if (ressource == 't' && tile.thystame)
        ret = 1;
    return ret;
}

int check_map_full(my_server_t *serv)
{
    int ret = 1;

    for (uint i = 0; i < serv->height; i++)
        for (uint j = 0; j < serv->width; j++)
            (!check_tile(serv->map[i][j])) ? (ret = 0) : (1);
    return ret;
}