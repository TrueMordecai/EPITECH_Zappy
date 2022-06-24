/*
** EPITECH PROJECT, 2022
** B-YEP-410-NAN-4-1-zappy-emile.ettel
** File description:
** ritual
*/

#include "server.h"

void ritual_proceed(my_server_t *serv, my_client_t *client, inv_t ritual,
int level)
{
    if (client->level == level)
        client->level++;
    client->inventory->linemate -= ritual.linemate;
    client->inventory->deraumere -= ritual.deraumere;
    client->inventory->sibur -= ritual.sibur;
    client->inventory->mendiane -= ritual.mendiane;
    client->inventory->phiras -= ritual.phiras;
    client->inventory->thystame -= ritual.thystame;
}

void check_rit_inv(my_server_t *serv, my_client_t *client, inv_t ritual,
int level)
{
    if (client->inventory->linemate < ritual.linemate)
        return;
    if (client->inventory->deraumere < ritual.deraumere)
        return;
    if (client->inventory->sibur < ritual.sibur)
        return;
    if (client->inventory->mendiane < ritual.mendiane)
        return;
    if (client->inventory->phiras < ritual.phiras)
        return;
    if (client->inventory->thystame < ritual.thystame)
        return;
    ritual_proceed(serv, client, ritual, level);
}

void check_ritual_high_level(my_server_t *serv, my_client_t *client, int level)
{
    switch (level) {
    case 5:
        check_rit_inv(serv, client, (inv_t)
        {.linemate=1, .deraumere=2, .sibur=1, .mendiane=3}, level);
        break;
    case 6:
        check_rit_inv(serv, client, (inv_t)
        {.linemate=1, .deraumere=2, .sibur=3, .phiras=1}, level);
        break;
    case 7:
        check_rit_inv(serv, client, (inv_t)
        {.linemate=2, .deraumere=2, .sibur=2,
            .mendiane=2, .phiras=2, .thystame=1}, level);
        break;
    default:
        break;
    }
}

void check_ritual_level(my_server_t *serv, my_client_t *client, int level)
{
    switch (level) {
    case 1:
        check_rit_inv(serv, client, (inv_t){.linemate=1}, level);
        break;
    case 2:
        check_rit_inv(serv, client, (inv_t)
        {.linemate=1, .deraumere=1, .sibur=1}, level);
        break;
    case 3:
        check_rit_inv(serv, client, (inv_t)
        {.linemate=2, .sibur=1, .phiras=2}, level);
        break;
    case 4:
        check_rit_inv(serv, client, (inv_t)
        {.linemate=1, .deraumere=1, .sibur=2, .phiras=1}, level);
        break;
    default:
        check_ritual_high_level(serv, client, level);
    }
}
