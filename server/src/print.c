/*
** EPITECH PROJECT, 2022
** B-YEP-410-NAN-4-1-zappy-emile.ettel
** File description:
** print
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

void print_cell(my_server_t *serv, int x, int y)
{
    if (serv->map[y][x].linemate > 0)
        printf("%i", serv->map[y][x].linemate);
    if (serv->map[y][x].deraumere > 0)
        printf("%i", serv->map[y][x].deraumere);
    if (serv->map[y][x].sibur > 0)
        printf("%i", serv->map[y][x].sibur);
    if (serv->map[y][x].mendiane > 0)
        printf("%i", serv->map[y][x].mendiane);
    if (serv->map[y][x].phiras > 0)
        printf("%i", serv->map[y][x].phiras);
    if (serv->map[y][x].thystame > 0)
        printf("%i", serv->map[y][x].thystame);
    if (serv->map[y][x].food > 0)
        printf("%i", serv->map[y][x].food);
}

void print_connected_client(my_client_t *cur, int i)
{
    printf("%i : Client with fd %i, named %s is connected\n"
    , i, cur->fd, cur->name);
    if (cur->message_queue_size != 0) {
        for (uint in = 0; in != cur->message_queue_size; in++) {
            printf("\t - %s\n", cur->message_queue[in]);
        }
    }
}

void print_all_clients(my_server_t *serv, char *message)
{
    my_client_t *cur = serv->clients;

    printf("\n#######################\n");
    printf("msg : %s\n", message);
    if (serv->gui_fd == -1)
        printf("No GUI Clients Detected\n");
    else
        printf("GUI is connected with fd %i\n", serv->gui_fd);
    if (!cur) {
        printf("No Player Clients Detected\n");
        return;
    }
    for (int i = 0; cur; i++) {
        print_connected_client(cur, i);
        cur = cur->next;
    }
}
