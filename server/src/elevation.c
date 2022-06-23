/*
** EPITECH PROJECT, 2022
** B-YEP-410-NAN-4-1-zappy-emile.ettel
** File description:
** elevation
*/

#include "server.h"

const inv_t costs[] = {
    {.linemate = 1},
    {.linemate = 1, .deraumere = 1, .sibur = 1},
    {.linemate = 2, .sibur = 1, .phiras = 2},
    {.linemate = 1, .deraumere = 1, .sibur = 2, .phiras = 1},
    {.linemate = 1, .deraumere = 2, .sibur = 1, .mendiane = 3},
    {.linemate = 1, .deraumere = 2, .sibur = 3, .phiras = 1},
    {.linemate = 2, .deraumere = 2, .sibur = 2, .mendiane = 2,
    .phiras = 2, .thystame = 1}
};

static int check_inv(my_client_t *client, inv_t ritual)
{
    if (client->inventory->linemate < ritual.linemate)
        return 0;
    if (client->inventory->deraumere < ritual.deraumere)
        return 0;
    if (client->inventory->sibur < ritual.sibur)
        return 0;
    if (client->inventory->mendiane < ritual.mendiane)
        return 0;
    if (client->inventory->phiras < ritual.phiras)
        return 0;
    if (client->inventory->thystame < ritual.thystame)
        return 0;
    return 1;
}

int check_other_clients(my_client_t *clients, my_client_t *client, int needed,
int *fds)
{
    int actual = 0;

    while (clients) {
        if (clients->x == client->x && clients->y == client-> y &&
            clients->level >= client->level && clients->cooldown == 0
            && check_inv(clients, costs[client->level -1]) && !clients->func &&
            clients->fd != client->fd && !clients->message_queue[0]) {
            fds[actual] = clients->fd;
            actual++;
        }
        clients = clients->next;
    }
    fds[actual] = client->fd;
    fds[actual + 1] = -1;
    return actual;
}

void set_cd(my_server_t *serv, int fd)
{
    my_client_t *client = get_client_from_fd(serv, fd);

    client->cooldown = 300;
    (client->cur) ? (free(client->cur)) : (0);
    client->cur = strdup("Participant");
}

int check_inc(my_server_t *serv, int fd)
{
    int needed = 0;
    int *fds;
    my_client_t *client = get_client_from_fd(serv, fd);

    (client->level <= 2) ? (needed = 1) : (0);
    (client->level <= 4) ? (needed = 3) : (0);
    (client->level <= 6) ? (needed = 5) : (0);
    fds = malloc(sizeof(int) * (100));
    if (check_inv(client, costs[client->level - 1])
    && check_other_clients(serv->clients, client, needed, fds) < needed) {
        free(fds);
        dprintf(fd, "ko\n");
        return 0;
    }
    for (int i = 0; fds[i] != -1; i++) {
        if (fds[i] != fd)
            set_cd(serv, fds[i]);
        dprintf(fds[i], "Elevation underway\n");
    }
    return 1;
}

int check_participants(my_client_t *clients, my_client_t *client, int needed,
int *fds)
{
    int actual = 0;

    while (clients) {
        if (clients->x == client->x && clients->y == client-> y &&
            clients->level >= client->level && clients->cooldown == 0
            && check_inv(clients, costs[client->level -1]) && !clients->func &&
            clients->fd != client->fd && !clients->message_queue[0] &&
            !strcmp(clients->cur, "Participant")) {
            fds[actual] = clients->fd;
            actual++;
        }
        clients = clients->next;
    }
    fds[actual] = client->fd;
    fds[actual + 1] = -1;
    return actual;
}

void incantation(my_server_t *serv, int fd)
{
    int needed = 0;
    int *fds;
    my_client_t *client = get_client_from_fd(serv, fd);

    (client->level <= 2) ? (needed = 1) : (0);
    (client->level <= 4) ? (needed = 3) : (0);
    (client->level <= 6) ? (needed = 5) : (0);
    fds = malloc(sizeof(int) * (100));
    if (check_inv(client, costs[client->level - 1])
    && check_other_clients(serv->clients, client, needed, fds) < needed) {
        free(fds);
        dprintf(fd, "ko\n");
        return;
    }
    for (int i = 0; fds[i] != -1; i++) {
        check_ritual_level(get_client_from_fd(serv, fds[i]), client->level);
        dprintf(fds[i], "Current level: %d\n",
        get_client_from_fd(serv, fds[i])->level);
    }
    return;
}
