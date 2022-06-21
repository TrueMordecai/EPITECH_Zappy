/*
** EPITECH PROJECT, 2022
** B-YEP-410-NAN-4-1-zappy-emile.ettel
** File description:
** set
*/

#include "server.h"

int set_aux(my_server_t *serv, my_client_t *client, char *cmd, int x)
{
    if (!strcmp(cmd[1], "sibur")) {
        serv->map[client->y][client->x].sibur += client->inventory.sibur;
        x = client->inventory.sibur;
        client->inventory.sibur = 0;
    }
    if (!strcmp(cmd[1], "mendiane")) {
        serv->map[client->y][client->x].mendiane += client->inventory.mendiane;
        x = client->inventory.mendiane;
        client->inventory.mendiane = 0;
    }
    if (!strcmp(cmd[1], "phiras")) {
        serv->map[client->y][client->x].phiras += client->inventory.phiras;
        x = client->inventory.phiras;
        client->inventory.phiras = 0;
    }
    if (!strcmp(cmd[1], "thystame")) {
        serv->map[client->y][client->x].thystame += client->inventory.thystame;
        x = client->inventory.thystame;
        client->inventory.thystame = 0;
    }
    return x;
}

void set(my_server_t *serv, int fd)
{
    my_client_t *client = get_client_from_fd(serv, fd);
    char **cmd = str_to_strarr(client->cur, " \n\r\t");
    int x = 0;

    if (!strcmp(cmd[1], "linemate")) {
        serv->map[client->y][client->x].linemate += client->inventory.linemate;
        x = client->inventory.linemate;
        client->inventory.linemate = 0;
    }
    if (!strcmp(cmd[1], "deraumere")) {
        serv->map[client->y][client->x].deraumere += client->inventory.deraumere;
        x = client->inventory.deraumere;
        client->inventory.deraumere = 0;
    }
    x = set_aux(serv, client, cmd, x);
    if (x > 0)
        dprintf(fd, "ok\n");
    else
        dprintf(fd, "ko\n");
    free_strarr(cmd);
}
