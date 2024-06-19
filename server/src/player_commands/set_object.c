/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** set_object
*/

#include "server.h"

// Initialize resources
void init_resources_set(resource_t *resources,
    server_t *serv, client_t *player)
{
    resources[0] = (resource_t){"food", &player->inv.food,
        &serv->map[player->y][player->x].resources.food};
    resources[1] = (resource_t){"linemate", &player->inv.linemate,
        &serv->map[player->y][player->x].resources.linemate};
    resources[2] = (resource_t){"deraumere", &player->inv.deraumere,
        &serv->map[player->y][player->x].resources.deraumere};
    resources[3] = (resource_t){"sibur", &player->inv.sibur,
        &serv->map[player->y][player->x].resources.sibur};
    resources[4] = (resource_t){"mendiane", &player->inv.mendiane,
        &serv->map[player->y][player->x].resources.mendiane};
    resources[5] = (resource_t){"phiras", &player->inv.phiras,
        &serv->map[player->y][player->x].resources.phiras};
    resources[6] = (resource_t){"thystame", &player->inv.thystame,
        &serv->map[player->y][player->x].resources.thystame};
    resources[7] = (resource_t){NULL, NULL, NULL};
}

// Drop object from inventory
int command_set_object(server_t *serv, client_t *player, char *arg)
{
    resource_t resources[8];

    init_resources_set(resources, serv, player);
    if (arg == NULL)
        return 1;
    for (int i = 0; resources[i].name != NULL; i++) {
        if (!strcmp(arg, resources[i].name) &&
            (*resources[i].player_resource) > 0) {
            (*resources[i].player_resource)--;
            (*resources[i].tile_resource)++;
            return success_response(player);
        }
    }
    return 1;
}
