/*
** EPITECH PROJECT, 2023
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** remove_egg.c
*/

#include "../include/main.h"

// Remove an egg from a team
void remove_egg_from_team(egg_t *egg, team_t *team)
{
    egg_t *current_team = team->eggs;

    if (current_team == egg) {
        team->eggs = egg->next_team;
        return;
    }
    while (current_team != NULL && current_team->next_team != egg)
        current_team = current_team->next_team;
    if (current_team != NULL)
        current_team->next_team = egg->next_team;
}

// Remove an egg from a tile
void remove_egg_from_tile(egg_t *egg, tile_t *tile)
{
    egg_t *current_tile = tile->eggs;

    if (current_tile == egg) {
        tile->eggs = egg->next_tile;
        return;
    }
    while (current_tile != NULL && current_tile->next_tile != egg)
        current_tile = current_tile->next_tile;
    if (current_tile != NULL)
        current_tile->next_tile = egg->next_tile;
}

// Remove an egg from the server
int remove_egg(egg_t *egg)
{
    team_t *team = NULL;
    tile_t *tile = NULL;

    if (egg == NULL)
        return 84;
    team = egg->team;
    tile = egg->tile;
    remove_egg_from_team(egg, team);
    remove_egg_from_tile(egg, tile);
    free(egg);
    return 0;
}

void destroy_eggs_from_tiles(tile_t *tile)
{
    egg_t *current_egg = NULL;
    egg_t *next_egg = NULL;

    if (tile == NULL)
        return;
    current_egg = tile->eggs;
    while (current_egg != NULL) {
        next_egg = current_egg->next_tile;
        remove_egg_from_team(current_egg, current_egg->team);
        remove_egg_from_tile(current_egg, tile);
        free(current_egg);
        current_egg = next_egg;
    }
    tile->eggs = NULL;
}

// Destroy all eggs from the server
void destroy_eggs(server_t *server)
{
    for (int x = 0; x < server->width; x++) {
        for (int y = 0; y < server->height; y++) {
            destroy_eggs_from_tiles(&server->map[x][y]);
        }
    }
}
