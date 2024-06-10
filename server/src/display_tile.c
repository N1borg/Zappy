/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** display_tile
*/

#include "../include/main.h"

int write_tile_content3(tile_t *tile, char *buffer)
{
    int ret = 0;

    if (tile->mendiane) {
        strcat(buffer, "mendiane ");
        ret++;
    }
    if (tile->phiras) {
        strcat(buffer, "phiras ");
        ret++;
    }
    if (tile->thystame) {
        strcat(buffer, "thystame ");
        ret++;
    }
    return ret;
}

int write_tile_content2(tile_t *tile, char *buffer)
{
    int ret = 0;

    if (tile->linemate) {
        strcat(buffer, "linemate ");
        ret++;
    }
    if (tile->deraumere) {
        strcat(buffer, "deraumere ");
        ret++;
    }
    if (tile->sibur) {
        strcat(buffer, "sibur ");
        ret++;
    }
    return (ret + write_tile_content3(tile, buffer));
}

// return 1 if tile is empty
int write_tile_content(tile_t *tile, char *buffer)
{
    int i = 0;
    int ret = 0;

    for (; i < MAX_CLIENTS && !tile->players[i]; i++);
    if (i < MAX_CLIENTS) {
        strcat(buffer, "player ");
        ret++;
    }
    if (tile->egg) {
        strcat(buffer, "egg ");
        ret++;
    }
    if (tile->food) {
        strcat(buffer, "food ");
        ret++;
    }
    return (ret + write_tile_content2(tile, buffer));
}

// Write the tile's content in thegiven buffer
void display_tile(tile_t *tile, char *buffer)
{
    int elements = write_tile_content(tile, buffer);

    buffer[strlen(buffer) - 1] = '\0';
    strcat(buffer, ", ");
}
