/*
** EPITECH PROJECT, 2022
** B-YEP-410-NAN-4-1-zappy-emile.ettel
** File description:
** get_cmd
*/

#include "server.h"

const cmd_list_t cmd_list[] = {
    {"Forward", 7, &forward},
    {"Right", 7, &right},
    {"Left", 7, &left},
    {"Look", 7, &look},
    {"Inventory", 1, &inventory},
    {"Broadcast", 7, &broadcast},
    {"Fork", 42, &fork_egg},
    {"Set", 7, &set},
    {"Take", 7, &take},
    {"Incantation", INCANTATION_TIME, &incantation},
    {"Eject", 7, &eject},
    {"Connect_nbr", 0, &connect_nbr}
};

fct_ptr get_cmd(char *str)
{
    for (int i = 0; i < COMMAND_LIST_SIZE; i++) {
        if (strncmp(cmd_list[i].name, str, strlen(cmd_list[i].name)) == 0)
            return cmd_list[i].fct;
    }
    return NULL;
}

int get_cd(char *str)
{
    for (int i = 0; i < COMMAND_LIST_SIZE; i++) {
        if (strncmp(cmd_list[i].name, str, strlen(cmd_list[i].name)) == 0)
            return cmd_list[i].cd;
    }
    return 0;
}
