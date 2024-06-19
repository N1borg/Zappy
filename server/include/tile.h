/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** tile
*/

#pragma once

#include "egg.h"
#include "player.h"

#define RESSOURCE_COUNT 7

typedef enum {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME
} resource_type_t;

typedef struct {
    const char *name;
    int *player_resource;
    int *tile_resource;
} resource_t;

typedef struct {
    char *name;
    double density;
} resource_density_t;

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
    egg_t *eggs;
    client_t *players[MAX_CLIENTS];
} tile_t;

void display_tile(tile_t *tile, char *buffer);
