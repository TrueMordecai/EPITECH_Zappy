/*
** EPITECH PROJECT, 2022
** B-YEP-410-NAN-4-1-zappy-emile.ettel
** File description:
** action_inventory
*/

#include "server.h"

void inventory(my_server_t *serv, int fd)
{
    my_client_t *cli = get_client_from_fd(serv, fd);

    dprintf(fd, "[food %d, linemate %d, deraumere %d, sibur %d, mendiane %d" \
    ", phiras %d, thystame %d]\n", cli->food, cli->inventory->linemate,
    cli->inventory->deraumere, cli->inventory->sibur
    , cli->inventory->mendiane, cli->inventory->phiras
    , cli->inventory->thystame);
}
