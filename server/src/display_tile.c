/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** display_tile
*/

#include "server.h"

// Write the tile's stones in the given buffer
void write_tile_stones(tile_t *tile, char *buffer)
{
    for (int i = 0; i < tile->resources.linemate; i++)
        strcat(buffer, "linemate ");
    for (int i = 0; i < tile->resources.deraumere; i++)
        strcat(buffer, "deraumere ");
    for (int i = 0; i < tile->resources.sibur; i++)
        strcat(buffer, "sibur ");
    for (int i = 0; i < tile->resources.mendiane; i++)
        strcat(buffer, "mendiane ");
    for (int i = 0; i < tile->resources.phiras; i++)
        strcat(buffer, "phiras ");
    for (int i = 0; i < tile->resources.thystame; i++)
        strcat(buffer, "thystame ");
}

void display_tile_eggs(tile_t *tile, char *buffer)
{
    egg_t *current_egg = tile->eggs;

    while (current_egg != NULL) {
        strcat(buffer, "egg ");
        current_egg = current_egg->next_tile;
    }
}

// Write the tile's objects in the given buffer
void write_tile_objects(tile_t *tile, char *buffer)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (tile->players[i])
            strcat(buffer, "player ");
    }
    display_tile_eggs(tile, buffer);
    for (int i = 0; i < tile->resources.food; i++)
        strcat(buffer, "food ");
}

// Write the tile's content in thegiven buffer
void display_tile(tile_t *tile, char *buffer)
{
    write_tile_objects(tile, buffer);
    write_tile_stones(tile, buffer);
    buffer[strlen(buffer) - 1] = '\0';
    strcat(buffer, ", ");
}
