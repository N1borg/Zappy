/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** tile
*/

#pragma once

#include "server.h"
#include "player.h"

typedef struct tile_s {
    int x;
    int y;
    int food;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
    int egg;
    client_t *players[MAX_CLIENTS];
} tile_t;

void display_tile(tile_t *tile, char *buffer);
