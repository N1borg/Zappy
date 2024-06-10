/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** init_resources
*/

#include "server.h"

// Initialize the resources on the map randomly
void init_resources(server_t *server)
{
    srand(time(NULL));
    int resource_count = sizeof(resources) / sizeof(resources[0]);

    for (int y = 0; y < server->height; y++)
        for (int x = 0; x < server->width; x++)
            init_resource_pointers(&server->map[y][x]);
    for (int i = 0; i < resource_count; i++)
        spread_resources(server, resources[i].density, resources[i].resource_ptr);
}
