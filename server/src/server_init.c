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
    for (int i = 0; i < MAX_CLIENTS; i++)
        tile->players[i] = NULL;
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

// initialize given client structure
void set_client(client_t *clients)
{
    clients->fd = 0;
    clients->x = 0;
    clients->y = 0;
    clients->level = 0;
    clients->orientation = 0;
    clients->food = 0;
    clients->linemate = 0;
    clients->deraumere = 0;
    clients->sibur = 0;
    clients->mendiane = 0;
    clients->phiras = 0;
    clients->thystame = 0;
    clients->team = NULL;
}

// Initializes the server struct
void init_server(server_t *s)
{
    s->master_socket = 0;
    for (int i = 0; i < MAX_CLIENTS; i++) {
        s->clients[i] = malloc(sizeof(client_t));
        set_client(s->clients[i]);
    }
    s->map = init_map(s->width, s->height);
    spawn_eggs(s->map, s->width, s->height,
        (s->max_client_team * (s->team_nb - 1)));
}
