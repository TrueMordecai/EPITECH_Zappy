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
    char **args;
    my_client_t *cur = serv->clients;
    ioctl(i, FIONREAD, &nread);
    if (nread == 0) {
        return;
    }
    buffer = get_client_line(i);
    args = str_to_strarr(buffer, " \t\r\n");
    for (; cur; cur = cur->next)
        if (cur->fd == i)
            break;

    if (!cur->team_name){
        set_team(cur, args, serv);
    } else
        add_to_queue(buffer, cur);
    free_strarr(args);
    free(buffer);
}

void incoming_message(my_server_t *serv, int i)
{
    struct sockaddr_in client;
    int cli_fd;

    if (FD_ISSET(i, &serv->tmp_fds)) { // if message
        if (i == serv->server_fd) { // If message from unknown source
            cli_fd = accept(serv->server_fd,
            (struct sockaddr *)&client, &serv->addr_len);
            FD_SET(cli_fd, &serv->fds);
            add_client(serv, make_client(cli_fd, serv->width, serv->height));
            dprintf(cli_fd, "%i %i\n", serv->width, serv->height);
            return;
        }
        get_message(serv, i);
    }
}

void check_tick(my_server_t *serv, clock_t *time)
{
    clock_t current;

    current = clock() - *time;
    if ((((float)current) / CLOCKS_PER_SEC) >= 1/(float)serv->freq) {
        update_clients(serv);
        if (!serv->map_cooldown) {
            update_map(serv);
            serv->map_cooldown = 16;
        } else
            serv->map_cooldown--;
        update_player_position(serv);
        // send_gui_map(serv);
        *time = clock();
    }
}

void server_loop(my_server_t *serv)
{
    struct timeval tv;
    clock_t time;
    int timeout;

    time = clock();
    tv.tv_sec = 0;
    tv.tv_usec = 1;
    while (1) {
        serv->tmp_fds = serv->fds;
        timeout = select(FD_SETSIZE, &serv->tmp_fds, NULL, NULL, &tv);
        if (timeout == 0) {
            check_tick(serv, &time);
            continue;
        }
        for (int i = 0; i < FD_SETSIZE; i++)
            incoming_message(serv, i);
    }
    close(serv->server_fd);
}