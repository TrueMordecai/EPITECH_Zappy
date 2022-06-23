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

int pickup(my_server_t *serv, my_client_t *cli, char *cmd, int x)
{
    if (!strcmp(cmd, "deraumere")) {
        cli->inventory->deraumere += serv->map[cli->y][cli->x].deraumere;
        x = serv->map[cli->y][cli->x].deraumere;
        serv->map[cli->y][cli->x].deraumere = 0;
    }
    if (!strcmp(cmd, "sibur")) {
        cli->inventory->sibur += serv->map[cli->y][cli->x].sibur;
        x = serv->map[cli->y][cli->x].sibur;
        serv->map[cli->y][cli->x].sibur = 0;
    }
    if (!strcmp(cmd, "mendiane")) {
        cli->inventory->mendiane += serv->map[cli->y][cli->x].mendiane;
        x = serv->map[cli->y][cli->x].mendiane;
        serv->map[cli->y][cli->x].mendiane = 0;
    }
    x = pickup_aux(serv, cli, cmd, x);
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
    if (x > 0) {
        dprintf(fd, "ok\n");
        gui_remove_resource(serv, cmd[1][0], client->x, client->y);
    } else {
        dprintf(fd, "ko\n");
    } 
    free_strarr(cmd);
}
