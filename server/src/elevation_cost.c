/*
** EPITECH PROJECT, 2022
** B-YEP-410-NAN-4-1-zappy-emile.ettel
** File description:
** elevation_cost
*/

#include "server.h"

int check_inv(my_client_t *client, inv_t ritual)
{
    if (client->inventory->linemate < ritual.linemate)
        return 0;
    if (client->inventory->deraumere < ritual.deraumere)
        return 0;
    if (client->inventory->sibur < ritual.sibur)
        return 0;
    if (client->inventory->mendiane < ritual.mendiane)
        return 0;
    if (client->inventory->phiras < ritual.phiras)
        return 0;
    if (client->inventory->thystame < ritual.thystame)
        return 0;
    return 1;
}
