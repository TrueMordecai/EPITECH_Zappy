/*
** EPITECH PROJECT, 2022
** B-NWP-400-NAN-4-1-myftp-emile.ettel
** File description:
** get_client_line
*/

#include "server.h"

char *get_client_line(int fd)
{
    char *buf = malloc(256);
    char one[1];
    int size = 0;

    if (fd < 0 || buf == NULL)
        return NULL;
    while (one[0] != '\n') {
        one[0] = 0;
        read(fd, one, 1);
        (one[0] != '\n') ? (buf[size] = one[0]) : (0);
        (one[0] != '\n') ? (size++) : (0);
    }
    buf[size] = 0;
    return buf;
}
