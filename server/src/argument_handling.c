/*
** EPITECH PROJECT, 2022
** B-YEP-410-NAN-4-1-zappy-emile.ettel
** File description:
** argument_handling
*/

#include "server.h"

void get_all_team_names(my_server_t *serv, char **argv, int argc, int i)
{
    int tmp;

    for (int j = i; j < argc; j++) {
        if (strncmp("-", argv[j], 1) != 0) {
            serv->nb_teams++;
        }
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
        if (!strcmp("-c", argv[i]))
            serv->clients_nb = atoi(argv[i + 1]);
        if (!strcmp("-f", argv[i]))
            serv->freq = atoi(argv[i + 1]);
    }
}