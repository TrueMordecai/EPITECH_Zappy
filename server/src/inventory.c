/*
** EPITECH PROJECT, 2022
** B-YEP-410-NAN-4-1-zappy-emile.ettel
** File description:
** inventory
*/

#include "../include/server.h"

inv_t *generate_inventory(void)
{
    inv_t new = malloc(sizeof(inv_t));

    if (!new)
        return NULL;
    new->food = 0;
    new->deraumere = 0;
    new->linemate = 0;
    new->sibur = 0;
    new->mendiane = 0;
    new->phiras = 0;
    new->thystame = 0;
    new->player = 0;

    return new;
}

inv_t *combine_inventory(inv_t *inv, inv_t *add)
{
    inv_t *new = malloc(sizeof(inv_t));

    if (!new)
        return NULL;
    new->food = inv->food + add->food;
    new->deraumere = inv->deraumere + add->deraumere;
    new->linemate = inv->linemate + add->linemate;
    new->sibur = inv->sibur + add->sibur;
    new->mendiane = inv->mendiane + add->mendiane;
    new->phiras = inv->phiras + add->phiras;
    new->thystame = inv->thystame + add->thystame;
    new->player = inv->player;
    return (new);
}
