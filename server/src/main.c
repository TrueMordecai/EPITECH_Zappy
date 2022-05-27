/*
** EPITECH PROJECT, 2022
** B-YEP-400-NAN-4-1-zappy-emile.ettel
** File description:
** main
*/

#include "server.h"


int free_and_ret(my_server_t *serv)
{
    free(serv);
    return 0;
}

void get_fd_set(my_server_t *serv)
{
    FD_ZERO(&serv->fds);
    FD_SET(serv->server_fd, &serv->fds);
}

my_server_t *get_server(my_server_t *serv, char **argv, int argc)
{
    int tmp;

    set_arguments(serv, argv, argc);
    serv->proto = getprotobyname("TCP");
    if (!serv->proto) {
        free(serv);
        return NULL;
    }
    tmp = serv->proto->p_proto;
    serv->server_fd = socket(AF_INET, SOCK_STREAM, tmp);
    if (serv->server_fd == -1) {
        free(serv);
        return NULL;
    }
    serv->addr_len = sizeof(serv->address);
    serv->address.sin_family = AF_INET;
    serv->address.sin_port = htons(serv->port);
    serv->address.sin_addr.s_addr = INADDR_ANY;
    return serv;
}

int make_server(my_server_t *serv, char **argv, int argc)
{
    serv = get_server(serv, argv, argc);
    if (!serv)
        return 0;
    if (bind(serv->server_fd, (struct sockaddr *)&(serv->address),
    serv->addr_len) < 0) {
        fprintf(stderr, "Error: Bind failed\n");
        close(serv->server_fd);
        return free_and_ret(serv);
    }
    if (listen(serv->server_fd, 42) < 0) {
        fprintf(stderr, "Error: Listen failed\n");
        close(serv->server_fd);
        return free_and_ret(serv);
    }
    get_fd_set(serv);
    return 1;
}

int main(int argc, char **argv)
{
    my_server_t *server;

    srand(time(NULL));
    if (argc == 2 && !strcmp(argv[1], "-help")) {
        printf("%s", USAGE_MSG);
        return 0;
    }
    if (!good_args(argc, argv)) {
        fprintf(stderr, "Error: Bad arguments\n");
        printf("%s", USAGE_MSG);
        return 84;
    }
    server = malloc(sizeof(my_server_t));
    if (server == NULL || !make_server(server, argv, argc))
        return 84;
    server_loop(server);
    free(server);
    return 0;
}
