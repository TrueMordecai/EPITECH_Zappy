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
    while (cur) {
        if (cur->fd == fd)
            return (cur);
        cur = cur->next;
    }
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

void print_all_clients(my_server_t *serv, char *message)
{
    int i = 0;

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
    while (cur) {
        printf ("%i : Client with fd %i, named %s is connected\n",i ,cur->fd, cur->name);
        if (cur->message_queue_size != 0) {
            for (uint in = 0; in != cur->message_queue_size; in++) {
                printf("\t - %s\n", cur->message_queue[in]);
            }
        }
        cur = cur->next;
        i++;
    }
}

int get_team_id(my_server_t *serv, char *team)
{
    int i = 0;

    for (; i < serv->nb_teams; i++)
        if (!strcmp(serv->team_names[i], team))
            return i;
    return -1;
}
