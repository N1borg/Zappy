/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** generate_resources.c
*/

#include "server.h"

// Place a resource on the map
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

// Generate the resources on the map randomly
void generate_resources(server_t *server)
{
    int x = 0;
    int y = 0;
    int total_resources = 0;

    for (int i = 0; i < RESSOURCE_COUNT; i++) {
        total_resources = server->width * server->height * resources[i].density;
        for (int placed = 0; placed < total_resources; placed++) {
            x = rand() % server->width;
            y = rand() % server->height;
            place_resource(server, x, y, i);
        }
    }
}
