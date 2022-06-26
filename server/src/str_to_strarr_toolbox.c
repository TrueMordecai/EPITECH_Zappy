/*
** EPITECH PROJECT, 2022
** B-YEP-410-NAN-4-1-zappy-emile.ettel
** File description:
** str_to_strarr_toolbox
*/

#include "server.h"

int str_char_cmp(char c, char *tok)
{
    for (int i = 0; tok[i]; i++) {
        if (c == tok[i])
            return (1);
    }
    return (0);
}

int str_len(char *str, char *tok)
{
    int i = 0;
    int quotes = 0;

    while (str[i] && quotes != 2) {
        if (str_char_cmp(str[i], tok) && quotes != 1)
            break;
        if (str[i] == '"')
            quotes++;
        i++;
    }
    return (i);
}

void free_strarr(char **arr)
{
    for (int i = 0; arr[i]; i++)
        free(arr[i]);
    free(arr);
}
