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

int add_quantity(inv_t inv, int nb, int add)
{
    switch (nb) {
        case 0:
            inv.deraumere += add;
            return 0;
        case 1:
            inv.linemate += add;
            return 0;
        case 2:
            inv.sibur += add;
            return 0;
        case 3:
            inv.mendiane += add;
            return 0;
        case 4:
            inv.phiras += add;
            return 0;
        case 5:
            inv.thystame += add;
            return 0;
    }
    return -1;
}