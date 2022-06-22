/*
** EPITECH PROJECT, 2022
** B-YEP-410-NAN-4-1-zappy-emile.ettel
** File description:
** pickup
*/

#include "server.h"

int pickup_aux(my_server_t *serv, my_client_t *client, char *cmd, int x)
{
    if (!strcmp(cmd, "phiras")) {
        client->inventory->phiras += serv->map[client->y][client->x].phiras;
        x = serv->map[client->y][client->x].phiras;
        serv->map[client->y][client->x].phiras = 0;
    }
    if (!strcmp(cmd, "thystame")) {
        client->inventory->thystame += serv->map[client->y][client->x].thystame;
        x = serv->map[client->y][client->x].thystame;
        serv->map[client->y][client->x].thystame = 0;
    }
    return x;
}

int pickup(my_server_t *serv, my_client_t *client, char *cmd, int x)
{
    if (!strcmp(cmd, "deraumere")) {
        client->inventory->deraumere += serv->map[client->y][client->x].deraumere;
        x = serv->map[client->y][client->x].deraumere;
        serv->map[client->y][client->x].deraumere = 0;
    }
    if (!strcmp(cmd, "sibur")) {
        client->inventory->sibur += serv->map[client->y][client->x].sibur;
        x = serv->map[client->y][client->x].sibur;
        serv->map[client->y][client->x].sibur = 0;
    }
    if (!strcmp(cmd, "mendiane")) {
        client->inventory->mendiane += serv->map[client->y][client->x].mendiane;
        x = serv->map[client->y][client->x].mendiane;
        serv->map[client->y][client->x].mendiane = 0;
    }
    x = pickup_aux(serv, client, cmd, x);
    return x;
}

void take(my_server_t *serv, int fd)
{
    my_client_t *client = get_client_from_fd(serv, fd);
    char **cmd = str_to_strarr(client->cur, " \n\r\t");
    int x = 0;

    if (!strcmp(cmd[1], "food")) {
        client->food += 126 * serv->map[client->y][client->x].food;
        x = serv->map[client->y][client->x].food;
        serv->map[client->y][client->x].food = 0;
    }
    if (!strcmp(cmd[1], "linemate")) {
        client->inventory->linemate += serv->map[client->y][client->x].linemate;
        x = serv->map[client->y][client->x].linemate;
        serv->map[client->y][client->x].linemate = 0;
    }
    x = pickup(serv, client, cmd[1], x);
    if (x > 0)
        dprintf(fd, "ok\n");
    else
        dprintf(fd, "ko\n");
    free_strarr(cmd);
}
