/*
** EPITECH PROJECT, 2022
** B-YEP-410-NAN-4-1-zappy-emile.ettel
** File description:
** argument_handling
*/

#include "server.h"

void set_team_sizes(my_server_t *serv)
{
    if (serv->clients_nb && serv->team_sizes)
        for (uint i = 0; i < serv->nb_teams; i++)
            serv->team_sizes[i] = serv->clients_nb;
}

void get_all_team_names(my_server_t *serv, char **argv, int argc, int i)
{
    int tmp = 0;

    for (int j = i; j < argc; j++) {
        if (strncmp("-", argv[j], 1) != 0)
            serv->nb_teams++;
        if (!strncmp("-", argv[j], 1))
            break;
    }
    serv->team_names = malloc(sizeof(char *) * (serv->nb_teams + 1));
    for (int j = i; j < argc; j++) {
        if (strncmp("-", argv[j], 1) != 0) {
            serv->team_names[tmp] = strdup(argv[j]);
            tmp++;
        }
        if (!strncmp("-", argv[j], 1))
            break;
    }
    serv->team_sizes = malloc(sizeof(int) * serv->nb_teams);
}

void set_arguments(my_server_t *serv, char **argv, int argc)
{
    serv->nb_teams = 0;
    serv->freq = 100;
    serv->map_cooldown = 0;
    serv->clients = NULL;
    for (int i = 1; i < argc; i++) {
        if (!strcmp("-p", argv[i]))
            serv->port = atoi(argv[i + 1]);
        if (!strcmp("-x", argv[i]))
            serv->height = atoi(argv[i + 1]);
        if (!strcmp("-y", argv[i]))
            serv->width = atoi(argv[i + 1]);
        if (!strcmp("-n", argv[i]))
            get_all_team_names(serv, argv, argc, i + 1);
        if (!strcmp("-c", argv[i])) {
            puts(argv[i + 1]);
            serv->clients_nb = atoi(argv[i + 1]);
            set_team_sizes(serv);
        }
        if (!strcmp("-f", argv[i]))
            serv->freq = atoi(argv[i + 1]);
    }
}