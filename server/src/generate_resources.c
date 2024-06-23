/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** generate_resources.c
*/

#include "server.h"
#include "tile.h"

/**
 * @brief Increment the resource count on a specific tile.
 *
 * @param serv A pointer to the server structure.
 * @param x The x-coordinate of the tile.
 * @param y The y-coordinate of the tile.
 * @param resource_type The type of resource to place.
 */
void place_resource_rare(server_t *serv, int x, int y, int resource_type)
{
    switch (resource_type) {
        case MENDIANE:
            serv->map[y][x].resources.mendiane++;
            break;
        case PHIRAS:
            serv->map[y][x].resources.phiras++;
            break;
        case THYSTAME:
            serv->map[y][x].resources.thystame++;
            break;
        default:
            break;
    }
}

/**
 * @brief Increment the resource count on a specific tile.
 *
 * @param serv A pointer to the server structure.
 * @param x The x-coordinate of the tile.
 * @param y The y-coordinate of the tile.
 * @param resource_type The type of resource to place.
 */
void place_resource_common(server_t *serv, int x, int y, int resource_type)
{
    switch (resource_type) {
        case FOOD:
            serv->map[y][x].resources.food++;
            break;
        case LINEMATE:
            serv->map[y][x].resources.linemate++;
            break;
        case DERAUMERE:
            serv->map[y][x].resources.deraumere++;
            break;
        case SIBUR:
            serv->map[y][x].resources.sibur++;
            break;
        default:
            place_resource_rare(serv, x, y, resource_type);
    }
}

/**
 * @brief Distribute resources across the map.
 *
 * @param serv A pointer to the server structure.
 * @param resource_type The type of resource to distribute.
 * @param total_resources The total number of resources to distribute.
 */
static void distribute_resources(server_t *serv,
    int resource_type, int total_resources)
{
    int x = 0;
    int y = 0;

    for (int j = 0; j < total_resources; j++) {
        x = rand() % serv->width;
        y = rand() % serv->height;
        place_resource_common(serv, x, y, resource_type);
    }
}

/**
 * @brief get the amount of a specific ressource on a given tile
 *
 * @param tile tile indicated by their position from the map
 * @param rsc_type type of resource used for an enum compare
 */
static int get_resource_from_tile(tile_t tile, int rsc_type)
{
    switch (rsc_type) {
        case FOOD:
            return tile.resources.food;
        case LINEMATE:
            return tile.resources.linemate;
        case DERAUMERE:
            return tile.resources.deraumere;
        case SIBUR:
            return tile.resources.sibur;
        case MENDIANE:
            return tile.resources.mendiane;
        case PHIRAS:
            return tile.resources.phiras;
        case THYSTAME:
            return tile.resources.thystame;
    }
    return 0;
}

/**
 * @brief count occurence number of a given resource
 *
 * @param serv A pointer to the server structure containing the map
 * @param rsc_type type of resource defined by their id
 */
static int count_ressource(server_t *serv, int rsc_type)
{
    int count = 0;

    for (int i = 0; i < serv->height; i++)
        for (int j = 0; j < serv->width; j++)
            count += get_resource_from_tile(serv->map[i][j], rsc_type);
    return count;
}

/**
 * @brief Generate resources on the map.
 *
 * @param serv A pointer to the server structure.
 */
void generate_resources(server_t *serv)
{
    int total_r = 0;
    int count = 0;
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
        count = count_ressource(serv, i);
        total_r = serv->width * serv->height * resources[i].density;
        distribute_resources(serv, i, total_r - count);
    }
}
