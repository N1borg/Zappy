/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** display_tile
*/

#include "../include/main.h"

void write_tile_stones(tile_t *tile, char *buffer)
{
    for (int i = 0; i < tile->linemate; i++)
        strcat(buffer, "linemate ");
    for (int i = 0; i < tile->deraumere; i++)
        strcat(buffer, "deraumere ");
    for (int i = 0; i < tile->sibur; i++)
        strcat(buffer, "sibur ");
    for (int i = 0; i < tile->mendiane; i++)
        strcat(buffer, "mendiane ");
    for (int i = 0; i < tile->phiras; i++)
        strcat(buffer, "phiras ");
    for (int i = 0; i < tile->thystame; i++)
        strcat(buffer, "thystame ");
}

// return 1 if tile is empty
void write_tile_objects(tile_t *tile, char *buffer)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (tile->players[i])
            strcat(buffer, "player ");
    }
    for (int i = 0; i < tile->egg; i++)
        strcat(buffer, "egg ");
    for (int i = 0; i < tile->food; i++)
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
