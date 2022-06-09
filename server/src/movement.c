/*
** EPITECH PROJECT, 2022
** B-YEP-410-NAN-4-1-zappy-emile.ettel
** File description:
** movement
*/

#include "server.h"

void forward(my_server_t *serv, my_client_t *client)
{
    if (client->direction == NORTH)
        client->y--;
    if (client->direction == EAST)
        client->x++;
    if (client->direction == SOUTH)
        client->y++;
    if (client->direction == WEST)
        client->x--;
}

void left(my_server_t *serv, my_client_t *client)
{
    if (client->direction == NORTH)
        client->direction = WEST;
    if (client->direction == EAST)
        client->direction = NORTH;
    if (client->direction == SOUTH)
        client->direction = EAST;
    if (client->direction == WEST)
        client->direction = SOUTH;
}

void right(my_server_t *serv, my_client_t *client)
{
    if (client->direction == NORTH)
        client->direction = EAST;
    if (client->direction == EAST)
        client->direction = SOUTH;
    if (client->direction == SOUTH)
        client->direction = WEST;
    if (client->direction == WEST)
        client->direction = NORTH;
}
