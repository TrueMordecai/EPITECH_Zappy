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

void separate_message_sent(my_server_t *serv, int fd)
{
    char *buffer;
    char **args;
    my_client_t *client = get_client_from_fd(serv, fd);

    if (!client)
        return;
    buffer = get_client_line(fd);
    args = str_to_strarr(buffer, " \t\r\n");
    if (connect_gui(serv, args, fd)) {
        free_strarr(args);
        free(buffer);
        print_all_clients(serv, "Gui is set");
        return;
    }
    printf("I Received %s ", buffer);
    if (!client->team_name)
        set_team(client, args, serv);
    else
        add_to_queue(buffer, client);
    free_strarr(args);
    free(buffer);
}

void handle_incoming_message_sender(my_server_t *serv, int i)
{
    struct sockaddr_in client;
    int cli_fd;

    if (FD_ISSET(i, &serv->tmp_fds)) {
        if (i == serv->server_fd) {
            cli_fd = accept(serv->server_fd,
            (struct sockaddr *)&client, &serv->addr_len);
            FD_SET(cli_fd, &serv->fds);
            add_client(serv, make_client(serv, cli_fd,
            serv->width, serv->height));
            print_all_clients(serv, "A new client appeared");
            dprintf(cli_fd, "msz %i %i\n", serv->width, serv->height);
            return;
        }
        separate_message_sent(serv, i);
    }
}

void check_tick(my_server_t *serv, clock_t *time)
{
    clock_t current;

    current = clock() - *time;
    if ((((float)current) / CLOCKS_PER_SEC) >= 1 / (float)serv->freq) {
        update_player_position(serv);
        update_clients(serv);
        if (!serv->map_cooldown) {
            update_map(serv);
            serv->map_cooldown = 20;
        } else
            serv->map_cooldown--;
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
    while (serv->win == false) {
        serv->tmp_fds = serv->fds;
        timeout = select(FD_SETSIZE, &serv->tmp_fds, NULL, NULL, &tv);
        for (int i = 0; i < FD_SETSIZE; i++)
            handle_incoming_message_sender(serv, i);
        if (timeout == 0) {
            check_tick(serv, &time);
            continue;
        }
    }
    close(serv->server_fd);
}
