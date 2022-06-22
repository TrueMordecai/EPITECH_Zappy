/*
** EPITECH PROJECT, 2022
** B-YEP-410-NAN-4-1-zappy-emile.ettel
** File description:
** set
*/

#include "server.h"

int set_aux_bis(my_server_t *serv, my_client_t *client, char *cmd, int x)
{
    if (!strcmp(cmd, "phiras")) {
        serv->map[client->y][client->x].phiras += client->inventory->phiras;
        x = client->inventory->phiras;
        client->inventory->phiras = 0;
    }
    if (!strcmp(cmd, "thystame")) {
        serv->map[client->y][client->x].thystame += client->inventory->thystame;
        x = client->inventory->thystame;
        client->inventory->thystame = 0;
    }
    return x;
}

int set_aux(my_server_t *serv, my_client_t *client, char *cmd, int x)
{
    if (!strcmp(cmd, "sibur")) {
        serv->map[client->y][client->x].sibur += client->inventory->sibur;
        x = client->inventory->sibur;
        client->inventory->sibur = 0;
    }
    if (!strcmp(cmd, "mendiane")) {
        serv->map[client->y][client->x].mendiane += client->inventory->mendiane;
        x = client->inventory->mendiane;
        client->inventory->mendiane = 0;
    }
    return set_aux_bis(serv, client, cmd, x);
}

void set(my_server_t *serv, int fd)
{
    my_client_t *cli = get_client_from_fd(serv, fd);
    char **cmd = str_to_strarr(cli->cur, " \n\r\t");
    int x = 0;

    if (!strcmp(cmd[1], "linemate")) {
        serv->map[cli->y][cli->x].linemate += cli->inventory->linemate;
        x = cli->inventory->linemate;
        cli->inventory->linemate = 0;
    }
    if (!strcmp(cmd[1], "deraumere")) {
        serv->map[cli->y][cli->x].deraumere += cli->inventory->deraumere;
        x = cli->inventory->deraumere;
        cli->inventory->deraumere = 0;
    }
    x = set_aux(serv, cli, cmd[1], x);
    if (x > 0)
        dprintf(fd, "ok\n");
    else
        dprintf(fd, "ko\n");
    free_strarr(cmd);
}
