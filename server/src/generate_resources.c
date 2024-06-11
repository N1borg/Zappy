/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** generate_resources.c
*/

#include "server.h"

/**
 * @brief Increment the resource count on a specific tile.
 * 
 * @param server A pointer to the server structure.
 * @param x The x-coordinate of the tile.
 * @param y The y-coordinate of the tile.
 * @param resource_type The type of resource to place.
 */
void place_resource(server_t *server, int x, int y, int resource_type)
{
    switch (resource_type) {
        case 0:
            server->map[y][x].food++;
        case 1:
            server->map[y][x].linemate++;
        case 2:
            server->map[y][x].deraumere++;
        case 3:
            server->map[y][x].sibur++;
        case 4:
            server->map[y][x].mendiane++;
        case 5:
            server->map[y][x].phiras++;
        case 6:
            server->map[y][x].thystame++;
        default:
            break;
    }
}

/**
 * @brief Distribute resources in a grid to be evenly spread across the map.
 * 
 * @param server A pointer to the server structure.
 * @param resource_type The type of resource to distribute.
 * @param total_resources The total number of resources to distribute.
 */
void distribute_resources_in_grid(server_t *server, int resource_type, int total_resources)
{
    int grid_size = sqrt(server->width * server->height / RESSOURCE_COUNT);
    int x = 0;
    int y = 0;

    for (int j = 0; j < total_resources; j++) {
        x = (j % (server->width / grid_size)) * grid_size + rand() % grid_size;
        y = (j / (server->width / grid_size)) * grid_size + rand() % grid_size;
        place_resource(server, x, y, resource_type);
    }
}

/**
 * @brief Generate resources on the map.
 * 
 * @param server A pointer to the server structure.
 */
void generate_resources(server_t *server)
{
    int total_resources = 0;

    for (int i = 0; i < RESSOURCE_COUNT; i++) {
        total_resources = server->width * server->height * resources[i].density;
        distribute_resources_in_grid(server, i, total_resources);
    }
}
