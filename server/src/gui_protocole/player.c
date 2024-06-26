/*
** EPITECH PROJECT, 2022
** B-YEP-410-NAN-4-1-zappy-emile.ettel
** File description:
** send_message_gui
*/

#include "server.h"

void gui_move_player(my_server_t *serv, my_client_t *client)
{
    dprintf(serv->gui_fd, "player move %s\n", client->name);
}

void gui_rotate_player(my_server_t *serv, my_client_t *client, e_rotation_t r)
{
    if (!client)
        return;
    if (serv->gui_fd == -1)
        return;
    if (r == R_LEFT)
        dprintf(serv->gui_fd, "player rotate %s L\n", client->name);
    else
        dprintf(serv->gui_fd, "player rotate %s R\n", client->name);
}

void gui_set_life_player(my_server_t *serv, my_client_t *client)
{
    if (!client)
        return;
    if (serv->gui_fd == -1)
        return;
    dprintf(serv->gui_fd, "player life %s %i\n", client->name, client->food);
}

void gui_talk_player(my_server_t *serv, my_client_t *client, char *message)
{
    (void)serv;
    (void)client;
}

void gui_new_player(my_server_t *serv, my_client_t *client)
{
    if (!client)
        return;
    if (serv->gui_fd == -1)
        return;
    dprintf(serv->gui_fd, "player new %i %i %i %s %s"
    , client->direction, client->x, client->y, client->team_name, client->name);
}
