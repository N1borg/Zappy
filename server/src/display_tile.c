/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** display_tile
*/

#include "../include/main.h"

int write_tile_contentmpt(tile_t *tile, char *buffer)
{
    int ret = 0;

    for (int i = 0; i < tile->mendiane; i++) {
        strcat(buffer, "mendiane ");
        ret++;
    }
    for (int i = 0; i < tile->phiras; i++) {
        strcat(buffer, "phiras ");
        ret++;
    }
    for (int i = 0; i < tile->thystame; i++) {
        strcat(buffer, "thystame ");
        ret++;
    }
    return ret;
}

int write_tile_contentlds(tile_t *tile, char *buffer)
{
    int ret = 0;

    for (int i = 0; i < tile->linemate; i++) {
        strcat(buffer, "linemate ");
        ret++;
    }
    for (int i = 0; i < tile->deraumere; i++) {
        strcat(buffer, "deraumere ");
        ret++;
    }
    for (int i = 0; i < tile->sibur; i++) {
        strcat(buffer, "sibur ");
        ret++;
    }
    return (ret + write_tile_contentmpt(tile, buffer));
}

// return 1 if tile is empty
int write_tile_contentpef(tile_t *tile, char *buffer)
{
    int ret = 0;

    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (tile->players[i]) {
            strcat(buffer, "player ");
            ret++;
        }
    }
    for (int i = 0; i < tile->egg; i++) {
        strcat(buffer, "egg ");
        ret++;
    }
    for (int i = 0; i < tile->food; i++) {
        strcat(buffer, "food ");
        ret++;
    }
    return (ret + write_tile_contentlds(tile, buffer));
}

// Write the tile's content in thegiven buffer
void display_tile(tile_t *tile, char *buffer)
{
    write_tile_contentpef(tile, buffer);
    buffer[strlen(buffer) - 1] = '\0';
    strcat(buffer, ", ");
}
