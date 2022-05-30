/*
** EPITECH PROJECT, 2022
** B-YEP-410-NAN-4-1-zappy-emile.ettel
** File description:
** generate_map_ressources
*/

#include "server.h"

inv_t add_ressource(inv_t map_inv, char tile, int *food)
{
    if (tile == 'f')
        *food = *food + 1;
    if (tile == 'l')
        map_inv.linemate++;
    if (tile == 'd')
        map_inv.deraumere++;
    if (tile == 's')
        map_inv.sibur++;
    if (tile == 'm')
        map_inv.mendiane++;
    if (tile == 'p')
        map_inv.phiras++;
    if (tile == 't')
        map_inv.thystame++;
    (void)food;
    return (map_inv);
}

int check_tile(char tile, my_server_t *serv, int chance, int pos[2])
{
    int pos_x = pos[0];
    int pos_y = pos[1];

    if (serv->map[pos[0]][pos[1]] == ' ' || rand() % chance == 0) {
        serv->map[pos[0]][pos[1]] = tile;
        return 1;
    }
    (void)pos_x;
    (void)pos_y;
    return 0;
}

void gen_ressource(int current, my_server_t *serv, char tile, int expected)
{
    int vec[2];

    while (current < expected) {
        vec[0] = rand() % serv->height;
        vec[1] = rand() % serv->width;
        current += check_tile(tile, serv, expected, vec);
    }
}

int calc_area(my_server_t *serv, int dens)
{
    int area = serv->width * serv->height;
    float density = (float)dens / 100.0;

    if ((float)area * density < 1)
        return 1;
    return (int)((float)area * density);
}

void update_map(my_server_t *serv)
{
    inv_t map_inv = generate_inventory();
    int food = 0;

    for (uint i = 0; i < serv->height; i++)
        for (uint j = 0; j < serv->width; j++)
            map_inv = add_ressource(map_inv, serv->map[i][j], &food);
    gen_ressource(food, serv, 'f', calc_area(serv, FOOD));
    gen_ressource(map_inv.linemate, serv, 'l', calc_area(serv, LINEMATE));
    gen_ressource(map_inv.deraumere, serv, 'd', calc_area(serv, DERAUMERE));
    gen_ressource(map_inv.sibur, serv, 's', calc_area(serv, SIBUR));
    gen_ressource(map_inv.mendiane, serv, 'm', calc_area(serv, MENDIANE));
    gen_ressource(map_inv.phiras, serv, 'p', calc_area(serv, PHIRAS));
    gen_ressource(map_inv.thystame, serv, 't', calc_area(serv, THYSTAME));
}