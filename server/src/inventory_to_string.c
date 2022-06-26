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
    new->egg = inv->egg;
    return new;
}

int count_total_items(inv_t *inv)
{
    int n = 0;

    n += inv->player;
    n += inv->egg;
    n += inv->food;
    n += inv->deraumere;
    n += inv->linemate;
    n += inv->sibur;
    n += inv->mendiane;
    n += inv->phiras;
    n += inv->thystame;
    return n;
}

char *add_other_item(inv_t *inv)
{
    if (inv->sibur > 0) {
        inv->sibur--;
        return "sibur";
    }
    if (inv->mendiane > 0) {
        inv->mendiane--;
        return "mendiane";
    }
    if (inv->phiras > 0) {
        inv->phiras--;
        return "phiras";
    }
    if (inv->thystame > 0) {
        inv->thystame--;
        return "thystame";
    }
    return "";
}

char *add_item_to_string(inv_t *inv)
{
    if (egg_presence(inv))
        return "egg";
    if (inv->player > 0) {
        inv->player--;
        return "player";
    }
    if (inv->food > 0) {
        inv->food--;
        return "food";
    }
    if (inv->deraumere > 0) {
        inv->deraumere--;
        return "deraumere";
    }
    if (inv->linemate > 0) {
        inv->linemate--;
        return "linemate";
    }
    return add_other_item(inv);
}

char *inventory_to_string(inv_t *inv)
{
    char buff[1024];
    char *tmp = buff;
    int n;
    char *item;
    inv_t *tmp_inv;

    if (!inv)
        return strdup("");
    n = count_total_items(inv);
    if (n == 0)
        return strdup("");
    tmp_inv = inv_dup(inv);
    tmp[0] = 0;
    for (int i = 0; i < n; i++) {
        item = add_item_to_string(tmp_inv);
        strcat(tmp, item);
        if (i + 1 < n)
            strcat(tmp, " ");
    }
    free(tmp_inv);
    return strdup(buff);
}
