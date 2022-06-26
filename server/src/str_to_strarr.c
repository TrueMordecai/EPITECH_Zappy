/*
** EPITECH PROJECT, 2022
** B-NWP-400-NAN-4-1-myftp-emile.ettel
** File description:
** str_to_strarr
*/

#include "server.h"

int get_next_arg_index(char *str, char *tok, int index)
{
    int i = index;

    while (str[i]) {
        if (!str_char_cmp(str[i], tok))
            break;
        i++;
    }
    return (i);
}

char *clip_quotes(char *str)
{
    if (str[0] == '"') {
        str[strlen(str) - 1] = '\0';
        return (str + 1);
    }
    return str;
}

char **str_to_strarr(char *str, char *tok)
{
    char **ret = malloc(sizeof(char *));
    char *buf = NULL;
    int index = get_next_arg_index(str, tok, 0);
    int i = 0;

    if (!ret || !str)
        return NULL;
    while (1) {
        if (!str[index]) {
            ret[i] = NULL;
            break;
        }
        buf = strndup(str + index, str_len(str + index, tok));
        index += str_len(str + index, tok);
        index = get_next_arg_index(str, tok, index);
        ret[i] = strdup(clip_quotes(buf));
        free(buf);
        i++;
        ret = realloc(ret, sizeof(char *) * (i + 2));
    }
    return ret;
}
