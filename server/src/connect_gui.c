/*
** EPITECH PROJECT, 2022
** B-YEP-410-NAN-4-1-zappy-emile.ettel
** File description:
** connect_gui
*/

#include "server.h"

bool my_strcmp(char *s1, char *s2)
{
    if (!s1 || !s2)
        return false;
    if (strlen(s1) != strlen(s2))
        return false;
    for (int i = 0; s1[i]; i++) {
        if (s1[i] != s2[i])
            return false;
    }
    return true;
}

bool is_gui_message(char **arr)
{
    if (!arr)
        return false;
    if (!arr[0])
        return false;
    if (!my_strcmp(arr[0], "GUI"))
        return false;
    if (!my_strcmp(arr[1], "GUI"))
        return false;
    if (!my_strcmp(arr[2], "GUI"))
        return false;
    return true;
}

void gui_server_catchup_send(my_server_t *s, int i, int j)
{
    inv_t **m = s->map;

    if (m[i][j].linemate > 0)
        dprintf(s->gui_fd, "l %i %c %c\n", m[i][j].linemate, j + 'a', i + 'a');
    if (m[i][j].deraumere > 0)
        dprintf(s->gui_fd, "d %i %c %c\n", m[i][j].deraumere, j + 'a', i + 'a');
    if (m[i][j].sibur > 0)
        dprintf(s->gui_fd, "s %i %c %c\n", m[i][j].sibur, j + 'a', i + 'a');
    if (m[i][j].mendiane > 0)
        dprintf(s->gui_fd, "m %i %c %c\n", m[i][j].mendiane, j + 'a', i + 'a');
    if (m[i][j].phiras > 0)
        dprintf(s->gui_fd, "p %i %c %c\n", m[i][j].phiras, j + 'a', i + 'a');
    if (m[i][j].thystame > 0)
        dprintf(s->gui_fd, "t %i %c %c\n", m[i][j].thystame, j + 'a', i + 'a');
    if (m[i][j].food > 0)
        dprintf(s->gui_fd, "f %i %c %c\n", m[i][j].food, j + 'a', i + 'a');
}

void gui_server_catchup(my_server_t *s)
{
    my_client_t *c = s->clients;
    while (c) {
        dprintf(s->gui_fd, "player new %i %i %i %s %s",
        c->direction, c->x, c->y, c->team_name, c->name);
        c = c->next;
    }
    for (uint i = 0; i < s->height; i++) {
        for (uint j = 0; j < s->width; j++) {
            gui_server_catchup_send(s, i, j);
        }
    }
}

bool connect_gui(my_server_t *serv, char **arr, int fd)
{
    my_client_t *cur = serv->clients;

    if (is_gui_message(arr) == false)
        return false;
    if (!cur)
        return false;
    while (cur) {
        if (cur->fd == fd) {
            serv->gui_fd = fd;
            cur->fd = -1;
            break;
        }
        cur = cur->next;
    }
    del_client(serv, -1);
    dprintf(serv->gui_fd, "msz %i %i\n", serv->width, serv->height);
    sleep(1);
    gui_server_catchup(serv);
    return true;
}
