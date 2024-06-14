/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** server_init
*/

#include "../include/main.h"

// Initializes a tile with the given coordinates
void set_tile(tile_t *tile, int x, int y)
{
    tile->x = x;
    tile->y = y;
    tile->food = 0;
    tile->linemate = 0;
    tile->deraumere = 0;
    tile->sibur = 0;
    tile->mendiane = 0;
    tile->phiras = 0;
    tile->thystame = 0;
    tile->egg = 0;
    tile->players = 0;
}

// Allocates memory for the map and initializes each tile
tile_t **init_map(int width, int height)
{
    tile_t **map = malloc(sizeof(tile_t *) * (width + 1));

    for (int i = 0; i < width; i++) {
        map[i] = malloc(sizeof(tile_t) * (height + 1));
        for (int j = 0; j < height; j++)
            set_tile(&map[i][j], i, j);
    }
    map[width] = NULL;
    return map;
}

// Spawns eggs randomly on the map
void spawn_eggs(tile_t **map, int width, int height, int num_eggs)
{
    int x = 0;
    int y = 0;

    for (int i = 0; i < num_eggs; i++) {
        x = rand() % width;
        y = rand() % height;
        map[x][y].egg++;
    }
}

// Initializes the server struct
void init_server(server_t *server)
{
    server->master_socket = 0;
    for (int i = 0; i < server->max_client_team; i++)
        server->client_socket[i] = 0;
    server->map = init_map(server->width, server->height);
    spawn_eggs(server->map, server->width, server->height,
        (server->max_client_team * server->team_nb));
}
