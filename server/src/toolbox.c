/*
** EPITECH PROJECT, 2022
** B-YEP-410-NAN-4-1-zappy-emile.ettel
** File description:
** toolbox
*/

#include "server.h"

my_client_t *get_client_from_fd(my_server_t *serv, int fd)
{
    my_client_t *cur = serv->clients;

    if (cur->fd == fd)
        return (cur);
    while (cur->next) {
        if (cur->fd == fd)
            return (cur);
        cur = cur->next;
    }
    puts ("Didn't find fd :(");
    return (NULL);
}

int count_client(my_server_t *serv)
{
    int res = 0;

    my_client_t *cur = serv->clients;
    if (!cur)
        return 0;
    while (cur->next) {
        cur = cur->next;
        res++;
    }
    return res;
}