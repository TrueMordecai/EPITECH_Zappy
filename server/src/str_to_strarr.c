/*
** EPITECH PROJECT, 2022
** B-NWP-400-NAN-4-1-myftp-emile.ettel
** File description:
** str_to_strarr
*/

#include "server.h"

char **str_to_strarr(char *str, char *tok)
{
    char **ret = malloc(sizeof(char *));
    char *buf = strtok(str, tok);
    int i = 0;

    if (!ret || !buf || !str)
        return NULL;
    for (;;) {
        ret[i] = strdup(buf);
        i++;
        ret = realloc(ret, sizeof(char *) * (i + 1));
        buf = strtok(NULL, tok);
        if (buf == NULL) {
            ret[i] = NULL;
            break;
        }
    }
    free(buf);
    return ret;
}

void free_strarr(char **arr)
{
    for (int i = 0; arr[i]; i++)
        free(arr[i]);
    free(arr);
}
