/*
** EPITECH PROJECT, 2022
** B-YEP-410-NAN-4-1-zappy-emile.ettel
** File description:
** inventory
*/

#include "../include/server.h"

inv_t generate_inventory(void)
{
    inv_t new;

    new.food = 0;
    new.deraumere = 0;
    new.linemate = 0;
    new.sibur = 0;
    new.mendiane = 0;
    new.phiras = 0;
    new.thystame = 0;
    new.player = 0;

    return new;
}

inv_t delete_inventory(inv_t inv)
{
    inv.food = 0;
    inv.deraumere = 0;
    inv.linemate = 0;
    inv.sibur = 0;
    inv.mendiane = 0;
    inv.phiras = 0;
    inv.thystame = 0;

    return inv;
}

inv_t combine_inventory(inv_t inv, inv_t add)
{
    inv.food += add.food;
    inv.deraumere += add.deraumere;
    inv.linemate += add.linemate;
    inv.sibur += add.sibur;
    inv.mendiane += add.mendiane;
    inv.phiras += add.phiras;
    inv.thystame += add.thystame;
    return (inv);
}
