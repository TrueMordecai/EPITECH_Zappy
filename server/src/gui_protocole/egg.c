/*
** EPITECH PROJECT, 2022
** B-YEP-410-NAN-4-1-zappy-emile.ettel
** File description:
** egg
*/

#include "server.h"

void gui_fork_player(my_server_t *serv, my_client_t *client)
{
    (void)serv;
    (void)client;
}

void gui_lay_player(my_server_t *serv, my_client_t *client)
{
    (void)serv;
    (void)client;
}

void gui_hatch_player(my_server_t *serv, my_client_t *client)
{
    (void)serv;
    (void)client;
}

void gui_elevation_player(my_server_t *serv, my_client_t *client)
{
    printf("player up %s\n", client->name);   
    dprintf(serv->gui_fd,"player up %s\n", client->name);
}