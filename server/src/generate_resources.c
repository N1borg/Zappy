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
    for (int y = 0; y < server->height; y++) {
        for (int x = 0; x < server->width; x++) {
            server->map[y][x].food += (rand() % 2 == 0) ? 1 : 0;
            server->map[y][x].linemate += (rand() % 100 < 30) ? 1 : 0;
            server->map[y][x].deraumere += (rand() % 100 < 15) ? 1 : 0;
            server->map[y][x].sibur += (rand() % 100 < 10) ? 1 : 0;
            server->map[y][x].mendiane += (rand() % 100 < 10) ? 1 : 0;
            server->map[y][x].phiras += (rand() % 100 < 8) ? 1 : 0;
            server->map[y][x].thystame += (rand() % 100 < 5) ? 1 : 0;
        }
    }
}
