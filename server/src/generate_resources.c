/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** generate_resources
*/

#include "server.h"

// Generate the resources on the map randomly
void generate_resources(server_t *server)
{
    srand(time(NULL));
    int resource_count = sizeof(resources) / sizeof(resources[0]);

    for (int i = 0; i < resource_count; i++)
        spread_resources(server, resources[i].density, resources[i].resource_ptr);
}
