/*
** EPITECH PROJECT, 2022
** B-YEP-410-NAN-4-1-zappy-emile.ettel
** File description:
** generate_map_ressources
*/

#include "server.h"

inv_t add_ressource(inv_t map_inv, inv_t tile)
{
    map_inv.food += tile.food;
    map_inv.deraumere += tile.deraumere;
    map_inv.linemate += tile.linemate;
    map_inv.sibur += tile.sibur;
    map_inv.mendiane += tile.mendiane;
    map_inv.phiras += tile.phiras;
    map_inv.thystame += tile.thystame;
    return (map_inv);
}

int add_on_tile(my_server_t *serv, char tile, int chance, int vec[2])
{
    if (rand() % chance != 0)
        return 0;
    if (check_tile_ressource(serv->map[vec[0]][vec[1]], tile) == 1)
        return 0;
    (tile == 'f') ? (serv->map[vec[0]][vec[1]].food++): (0);
    (tile == 'd') ? (serv->map[vec[0]][vec[1]].deraumere++): (0);
    (tile == 'l') ? (serv->map[vec[0]][vec[1]].linemate++): (0);
    (tile == 's') ? (serv->map[vec[0]][vec[1]].sibur++): (0);
    (tile == 'm') ? (serv->map[vec[0]][vec[1]].mendiane++): (0);
    (tile == 'p') ? (serv->map[vec[0]][vec[1]].phiras++): (0);
    (tile == 't') ? (serv->map[vec[0]][vec[1]].thystame++): (0);
    gui_spawn_resource(serv, tile, vec[1], vec[0]);
    return 1;
}

void gen_ressource(int current, my_server_t *serv, char tile, int expected)
{
    int vec[2];

    while (current < expected && check_map_full(serv) == 0) {
        vec[0] = rand() % serv->height;
        vec[1] = rand() % serv->width;
        if (check_tile(serv->map[vec[0]][vec[1]]) == 0)
            current += add_on_tile(serv, tile, expected, vec);
    }
    while (current < expected) {
        vec[0] = rand() % serv->height;
        vec[1] = rand() % serv->width;
        current += add_on_tile(serv, tile, expected, vec);
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
    inv_t *map_inv = generate_inventory();

    for (uint i = 0; i < serv->height; i++)
        for (uint j = 0; j < serv->width; j++)
            *map_inv = add_ressource(*map_inv, serv->map[i][j]);
    gen_ressource(map_inv->food, serv, 'f', calc_area(serv, FOOD));
    gen_ressource(map_inv->linemate, serv, 'l', calc_area(serv, LINEMATE));
    gen_ressource(map_inv->deraumere, serv, 'd', calc_area(serv, DERAUMERE));
    gen_ressource(map_inv->sibur, serv, 's', calc_area(serv, SIBUR));
    gen_ressource(map_inv->mendiane, serv, 'm', calc_area(serv, MENDIANE));
    gen_ressource(map_inv->phiras, serv, 'p', calc_area(serv, PHIRAS));
    gen_ressource(map_inv->thystame, serv, 't', calc_area(serv, THYSTAME));
}
