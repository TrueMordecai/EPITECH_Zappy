/*
** EPITECH PROJECT, 2022
** B-YEP-400-NAN-4-1-zappy-emile.ettel
** File description:
** server_loop
*/

#include "server.h"

void server_loop(my_server_t *serv)
{
    struct sockaddr_in client;
    int client_fd;
    char buffer;

    while (1) {
        serv->tmp_fds = serv->fds;
        select(FD_SETSIZE, &serv->tmp_fds, NULL, NULL, NULL);
        for (int i = 0; i < FD_SETSIZE; i++) {
            if (FD_ISSET(i, &serv->tmp_fds)) {
                if (i == serv->server_fd) {
                    client_fd = accept(serv->server_fd,
                        (struct sockaddr *)&client, &serv->addr_len);
                    FD_SET(client_fd, &serv->fds);
                } else {
                    while (1) {
                        read(i, &buffer, 1);
                        write(1, &buffer, 1);
                        if (buffer == '\n')
                            break;
                    }
                }
            }
        }
        (void)client_fd;
    }
    close(serv->server_fd);
}