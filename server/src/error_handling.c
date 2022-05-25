/*
** EPITECH PROJECT, 2022
** B-YEP-410-NAN-4-1-zappy-emile.ettel
** File description:
** argument_handling
*/

#include "server.h"

arg_checklist_t init_checklist(void)
{
    arg_checklist_t checklist;

    checklist.clientsNb = false;
    checklist.names = false;
    checklist.height = false;
    checklist.width = false;
    checklist.port = false;
    return checklist;
}

bool check_arg(int argc, char **argv, int i)
{
    if (argc <= i + 1)
        return false;
    if (!(!strcmp("-c", argv[i]) || !strcmp("-p", argv[i]) ||
    !strcmp("-x", argv[i]) || !strcmp("-y", argv[i])))
        return true;
    for (int j = 0; argv[i + 1][j]; j++)
        if (!isdigit(argv[i + 1][j]))
            return false;
    return true;
}

int check_checklist(arg_checklist_t checklist)
{
    if (!checklist.port || !checklist.width || !checklist.height ||
    !checklist.names || !checklist.clientsNb) {
        fprintf(stderr, "Error: Missing arguments\n");
        return false;
    }
    return true;
}

int good_args(int argc, char **argv)
{
    arg_checklist_t checklist = init_checklist();
    int repeat = 0;
    bool good_args = true;

    for (int i = 0; i < argc; i++) {
        if (!strcmp("-p", argv[i]))
            (!checklist.port) ? (checklist.port = 1) : (repeat = 1);
        if (!strcmp("-x", argv[i]))
            (!checklist.height) ? (checklist.height = 1) : (repeat = 1);
        if (!strcmp("-y", argv[i]))
            (!checklist.width) ? (checklist.width = 1) : (repeat = 1);
        if (!strcmp("-n", argv[i]))
            (!checklist.names) ? (checklist.names = 1) : (repeat = 1);
        if (!strcmp("-c", argv[i]))
            (!checklist.clientsNb) ? (checklist.clientsNb = 1) : (repeat = 1);
        if (!strncmp("-", argv[i], 1))
            good_args = check_arg(argc, argv, i);
        if (good_args == false || repeat == 1)
            return 0;
    }
    return check_checklist(checklist);
}