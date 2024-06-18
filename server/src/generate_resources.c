/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** generate_resources.c
*/

#include "../include/main.h"

/**
 * @brief Increment the resource count on a specific tile.
 *
 * @param server A pointer to the server structure.
 * @param x The x-coordinate of the tile.
 * @param y The y-coordinate of the tile.
 * @param resource_type The type of resource to place.
 */
void place_resource_rare(server_t *server, int x, int y, int resource_type)
{
    switch (resource_type) {
        case MENDIANE:
            server->map[y][x].mendiane++;
            break;
        case PHIRAS:
            server->map[y][x].phiras++;
            break;
        case THYSTAME:
            server->map[y][x].thystame++;
            break;
        default:
            break;
    }
}

/**
 * @brief Increment the resource count on a specific tile.
 *
 * @param server A pointer to the server structure.
 * @param x The x-coordinate of the tile.
 * @param y The y-coordinate of the tile.
 * @param resource_type The type of resource to place.
 */
void place_resource_common(server_t *server, int x, int y, int resource_type)
{
    switch (resource_type) {
        case FOOD:
            server->map[y][x].food++;
            break;
        case LINEMATE:
            server->map[y][x].linemate++;
            break;
        case DERAUMERE:
            server->map[y][x].deraumere++;
            break;
        case SIBUR:
            server->map[y][x].sibur++;
            break;
        default:
            place_resource_rare(server, x, y, resource_type);
    }
}

/**
 * @brief Distribute resources across the map.
 *
 * @param server A pointer to the server structure.
 * @param resource_type The type of resource to distribute.
 * @param total_resources The total number of resources to distribute.
 */
void distribute_resources(server_t *server,
    int resource_type, int total_resources)
{
    int x = 0;
    int y = 0;

    for (int j = 0; j < total_resources; j++) {
        x = rand() % server->width;
        y = rand() % server->height;
        place_resource_common(server, x, y, resource_type);
    }
}

/**
 * @brief Generate resources on the map.
 *
 * @param server A pointer to the server structure.
 */
void generate_resources(server_t *server)
{
    int total_r = 0;
    resource_density_t resources[RESSOURCE_COUNT] = {
        {"food", 0.5},
        {"linemate", 0.3},
        {"deraumere", 0.15},
        {"sibur", 0.1},
        {"mendiane", 0.1},
        {"phiras", 0.08},
        {"thystame", 0.05}
    };

    for (int i = 0; i < RESSOURCE_COUNT; i++) {
        total_r = server->width * server->height * resources[i].density;
        distribute_resources(server, i, total_r);
    }
}
