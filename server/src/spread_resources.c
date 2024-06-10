/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** spread_resources
*/

#include "server.h"

// Spread the resources on the map randomly
void spread_resources(server_t *server, double density, int *resource_ptr)
{
    int total_resources = (int)(server->width * server->height * density);
    int placed = 0;

    while (placed < total_resources) {
        int x = rand() % server->width;
        int y = rand() % server->height;
        *(resource_ptr + y * server->width + x) += 1;
        placed++;
    }
}
