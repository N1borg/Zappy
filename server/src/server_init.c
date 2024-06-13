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
    tile->eggs = NULL;
    for (int i = 0; i < MAX_CLIENTS; i++)
        tile->players[i] = NULL;
}

// Allocates memory for the map and initializes each tile
tile_t **init_map(int width, int height)
{
    tile_t **map = malloc(sizeof(tile_t *) * (height + 1));

    for (int i = 0; i < height; i++) {
        map[i] = malloc(sizeof(tile_t) * (width + 1));
        for (int j = 0; j < width; j++)
            set_tile(&map[i][j], i, j);
    }
    map[height] = NULL;
    return map;
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

// Adds an egg to the server
int add_egg(team_t *team, tile_t *tile)
{
    egg_t *new_egg = malloc(sizeof(egg_t));
    egg_t *tile_egg = NULL;

    if (new_egg == NULL)
        return 84;
    new_egg->tile = tile;
    new_egg->team = team;
    new_egg->next = NULL;
    new_egg->next = team->eggs;
    team->eggs = new_egg;
    tile_egg = tile->eggs;
    if (tile_egg == NULL) {
        tile->eggs = new_egg;
    } else {
        while (tile_egg->next != NULL) {
            tile_egg = tile_egg->next;
        }
        tile_egg->next = new_egg;
    }
    return 0;
}

// Initializes the server struct
void init_server(server_t *s)
{
    int x = 0;
    int y = 0;

    s->master_socket = 0;
    for (int i = 0; i < MAX_CLIENTS; i++) {
        s->clients[i] = malloc(sizeof(client_t));
        set_client(s->clients[i]);
    }
    s->map = init_map(s->width, s->height);
    for (int i = 0; i < s->team_nb - 1; i++) {
        for (int j = 0; j < s->max_client_team; j++) {
            x = rand() % s->width;
            y = rand() % s->height;
            add_egg(s->teams[i], &s->map[x][y]);
        }
    }
}
