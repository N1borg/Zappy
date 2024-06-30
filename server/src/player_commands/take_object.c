/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** take_object
*/

#include "server.h"

// Initialize resources
void init_resources_take(resource_t *resources,
    server_t *serv, client_t *player)
{
    resources[0] = (resource_t){"food", 0, &player->inv.food,
        &serv->map[player->y][player->x].resources.food};
    resources[1] = (resource_t){"linemate", 1, &player->inv.linemate,
        &serv->map[player->y][player->x].resources.linemate};
    resources[2] = (resource_t){"deraumere", 2, &player->inv.deraumere,
        &serv->map[player->y][player->x].resources.deraumere};
    resources[3] = (resource_t){"sibur", 3, &player->inv.sibur,
        &serv->map[player->y][player->x].resources.sibur};
    resources[4] = (resource_t){"mendiane", 4, &player->inv.mendiane,
        &serv->map[player->y][player->x].resources.mendiane};
    resources[5] = (resource_t){"phiras", 5, &player->inv.phiras,
        &serv->map[player->y][player->x].resources.phiras};
    resources[6] = (resource_t){"thystame", 6, &player->inv.thystame,
        &serv->map[player->y][player->x].resources.thystame};
    resources[7] = (resource_t){NULL, -1, NULL, NULL};
}

// Take object to inventory
int command_take_object(server_t *serv, client_t *player, char *arg)
{
    resource_t resources[8];

    init_resources_take(resources, serv, player);
    if (arg == NULL)
        return 1;
    for (int i = 0; resources[i].name != NULL; i++) {
        if (!strcmp(arg, resources[i].name) &&
            (*resources[i].tile_resource) > 0) {
            (*resources[i].tile_resource)--;
            (*resources[i].player_resource)++;
            event_pgt(serv, player, resources[i].graphic_name);
            return success_response(player);
        }
    }
    return 1;
}
