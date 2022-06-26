/*
** EPITECH PROJECT, 2022
** B-YEP-410-NAN-4-1-zappy-emile.ettel
** File description:
** get_base_pos
*/

#include "server.h"

int get_base_x(orientation_t dir, int x)
{
    if (x > 0) {
        if (dir == SOUTH)
            return 1;
        if (dir == NORTH)
            return 5;
        if (dir == EAST)
            return 3;
        if (dir == WEST)
            return 7;
    } else {
        if (dir == SOUTH)
            return 5;
        if (dir == NORTH)
            return 1;
        if (dir == EAST)
            return 7;
        if (dir == WEST)
            return 3;
    }
    return 0;
}

int get_base_y(orientation_t dir, int y)
{
    if (y > 0) {
        if (dir == EAST)
            return 1;
        if (dir == WEST)
            return 5;
        if (dir == NORTH)
            return 3;
        if (dir == SOUTH)
            return 7;
    } else {
        if (dir == EAST)
            return 5;
        if (dir == WEST)
            return 1;
        if (dir == NORTH)
            return 7;
        if (dir == SOUTH)
            return 3;
    }
    return 0;
}
