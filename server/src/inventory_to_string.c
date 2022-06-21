/*
** EPITECH PROJECT, 2022
** B-YEP-410-NAN-4-1-zappy-emile.ettel
** File description:
** inventory_to_string
*/

#include "server.h"

inv_t *inv_dup(inv_t *inv)
{
    inv_t *new = malloc(sizeof(inv_t));

    new->player = inv->player;
    new->food = inv->food;
    new->deraumere = inv->deraumere;
    new->linemate = inv->linemate;
    new->sibur = inv->sibur;
    new->mendiane = inv->mendiane;
    new->phiras = inv->phiras;
    new->thystame = inv->thystame;

    return new;
}

int count_total_items(inv_t *inv)
{
    int n = 0;

    n += inv->player;
    n += inv->food;
    n += inv->deraumere;
    n += inv->linemate;
    n += inv->sibur;
    n += inv->mendiane;
    n += inv->phiras;
    n += inv->thystame;

    return n;
}

void add_other_item(char *str, inv_t *inv)
{
    if (inv->sibur > 0) {
        strcat(str, "sibur");
        inv->sibur--;
        return;
    }
    if (inv->mendiane > 0) {
        strcat(str, "mendiane");
        inv->mendiane--;
        return;
    }
    if (inv->phiras > 0) {
        strcat(str, "phiras");
        inv->phiras--;
        return;
    }
    if (inv->thystame > 0) {
        strcat(str, "thystame");
        inv->thystame--;
        return;
    }
}

void add_item_to_string(char *str, inv_t *inv)
{
    if (inv->player > 0) {
        strcat(str, "player");
        inv->player--;
        return;
    }
    if (inv->food > 0) {
        strcat(str, "food");
        inv->food--;
        return;
    }
    if (inv->deraumere > 0) {
        strcat(str, "deraumere");
        inv->deraumere--;
        return;
    }
    if (inv->linemate > 0) {
        strcat(str, "linemate");
        inv->linemate--;
        return;
    }
    return add_other_item(str, inv);
}

char *inventory_to_string(inv_t *inv)
{
    char buff[1024];
    char *tmp = buff;
    int n;
    inv_t *tmp_inv;

    if (!inv)
        return strdup("");
    n = count_total_items(inv);
    if (n == 0)
        return strdup("");
    tmp[0] = 0;
    tmp_inv = inv_dup(inv);
    for (int i = 0; i < n; i++) {
        add_item_to_string(tmp, tmp_inv);
        if (i + 1 < n)
            strcat(tmp, " ");
    }
    free(tmp_inv);
    return strdup(buff);
}
