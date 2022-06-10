/*
** EPITECH PROJECT, 2022
** B-YEP-410-NAN-4-1-zappy-emile.ettel
** File description:
** send_message_gui
*/

#include "server.h"

void gui_new_player(int fd, my_server_t *serv)
{
    my_client_t *tp = get_client_from_fd(serv, fd);

    puts ("Try to sent message to gui\n");
    if (tp == NULL) {
        return;
    }
    //puts (tp->team_name);
    if (serv->gui_fd == -1) {
        puts ("No GUI is connected");
    }
    puts ("Sent new player to gui\n");
    dprintf(serv->gui_fd, "player new %i %i %i %s %s", tp->direction, tp->x, tp->y, tp->team_name, tp->name);
}