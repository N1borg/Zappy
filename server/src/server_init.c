/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** server_init
*/

#include "server.h"

// Initializes a tile with the given coordinates
void set_tile(tile_t *tile, int x, int y)
{
    tile->x = x;
    tile->y = y;
    tile->resources.food = 0;
    tile->resources.linemate = 0;
    tile->resources.deraumere = 0;
    tile->resources.sibur = 0;
    tile->resources.mendiane = 0;
    tile->resources.phiras = 0;
    tile->resources.thystame = 0;
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

// Initialize given client structure
void set_client(client_t *clients)
{
    clients->fd = 0;
    clients->id = 0;
    clients->x = 0;
    clients->y = 0;
    clients->level = 0;
    clients->is_incanting = false;
    clients->orientation = 0;
    clients->inv.food = 10;
    clients->inv.linemate = 0;
    clients->inv.deraumere = 0;
    clients->inv.sibur = 0;
    clients->inv.mendiane = 0;
    clients->inv.phiras = 0;
    clients->inv.thystame = 0;
    clients->team = NULL;
    clients->command_queue = NULL;
}

void add_new_egg(server_t *serv, client_t *client, team_t *team, tile_t *tile)
{
    egg_t *new_egg = add_egg(team, tile);

    if (new_egg == NULL)
        disconnect_client(serv, client);
    else
        event_enw(serv, client, new_egg);
}

// Initializes the server struct
void init_server(server_t *serv)
{
    int x = 0;
    int y = 0;

    serv->master_socket = 0;
    for (int i = 0; i < MAX_CLIENTS; i++) {
        serv->clients[i] = malloc(sizeof(client_t));
        set_client(serv->clients[i]);
    }
    serv->map = init_map(serv->width, serv->height);
    for (int i = 0; i < serv->team_nb - 1; i++) {
        for (int j = 0; j < serv->max_client_team; j++) {
            x = rand() % serv->width;
            y = rand() % serv->height;
            add_new_egg(serv, serv->clients[i],
                serv->teams[i], &serv->map[x][y]);
        }
    }
}
