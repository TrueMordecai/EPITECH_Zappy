/*
** EPITECH PROJECT, 2022
** B-YEP-410-NAN-4-1-zappy-emile.ettel
** File description:
** connect_gui
*/

#include "server.h"

void print_arr(char **arr)
{
    puts("Printing Arr :");
    for (int i = 0; arr[i]; i++) {
        puts(arr[i]);
    }
    puts("END");
}

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

void gui_spawn_all_ressources(my_server_t *s)
{
    puts("dprint all ressources");
    for (uint i = 0; i < s->height; i++) {
        for (uint j = 0; j < s->width; j++) {
            dprintf(s->gui_fd, "m l %i %i %i\n" , s->map[i][j].linemate, i, j);
            dprintf(s->gui_fd, "m d %i %i %i\n" , s->map[i][j].deraumere, i, j);
            dprintf(s->gui_fd, "m s %i %i %i\n" , s->map[i][j].sibur, i, j);
            dprintf(s->gui_fd, "m m %i %i %i\n" , s->map[i][j].mendiane, i, j);
            dprintf(s->gui_fd, "m p %i %i %i\n" , s->map[i][j].phiras, i, j);
            dprintf(s->gui_fd, "m t %i %i %i\n" , s->map[i][j].thystame, i, j);
            dprintf(s->gui_fd, "m f %i %i %i\n" , s->map[i][j].food, i, j);
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
            //puts("Gui fd is well set");
            serv->gui_fd = fd;
            cur->fd = -1;
            break;
        }
        cur = cur->next;
    }
    del_client(serv, -1);
    dprintf(serv->gui_fd, "msz %i %i\n", serv->width, serv->height);
    sleep(1); // Useful so gui can create map
    gui_spawn_all_ressources(serv);
    return true;
}
