/*
** EPITECH PROJECT, 2022
** B-YEP-400-NAN-4-1-zappy-emile.ettel
** File description:
** server_loop
*/

#include "server.h"
#include <sys/ioctl.h>

int client_list_count(my_client_t *clients)
{
    int count = 0;

    for (; clients; clients = clients->next)
        count++;
    return count;
}

void get_message(my_server_t *serv, int i)
{
    int nread;
    char *buffer;

    ioctl(i, FIONREAD, &nread);
    if (nread == 0) {
        del_client(serv, i);
        FD_CLR(i, &serv->fds);
        return;
    }
    buffer = get_client_line(i);
    printf("%s\n", buffer);
    free(buffer);
}

void incoming_message(my_server_t *serv, int i)
{
    struct sockaddr_in client;
    int cli_fd;

    if (FD_ISSET(i, &serv->tmp_fds)) {
        if (i == serv->server_fd) {
            cli_fd = accept(serv->server_fd,
            (struct sockaddr *)&client, &serv->addr_len);
            FD_SET(cli_fd, &serv->fds);
            add_client(serv, make_client(cli_fd, serv->width,
            serv->height));
            return;
        }
        get_message(serv, i);
    }
}

void server_loop(my_server_t *serv)
{
    while (1) {
        serv->tmp_fds = serv->fds;
        select(FD_SETSIZE, &serv->tmp_fds, &serv->tmp_fds, NULL, NULL);
        for (int i = 0; i < FD_SETSIZE; i++)
            incoming_message(serv, i);
        printf("Connected clients: %d\n", client_list_count(serv->clients));
    }
    close(serv->server_fd);
}