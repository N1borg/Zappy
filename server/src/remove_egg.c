/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** remove_egg.c
*/

#include "server.h"

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
    team->free_slots--;
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

// Destroy all eggs from a tile
int destroy_eggs_from_tiles(server_t *server, tile_t *tile)
{
    egg_t *current_egg = NULL;
    egg_t *next_egg = NULL;
    int nbr_eggs_destroyed = 0;

    if (tile == NULL)
        return 0;
    current_egg = tile->eggs;
    while (current_egg != NULL) {
        event_edi(server, current_egg);
        next_egg = current_egg->next_tile;
        remove_egg_from_team(current_egg, current_egg->team);
        remove_egg_from_tile(current_egg, tile);
        free(current_egg);
        nbr_eggs_destroyed++;
        current_egg = next_egg;
    }
    tile->eggs = NULL;
    return nbr_eggs_destroyed;
}

void destroy_eggs_pointer(egg_t *eggs)
{
    egg_t *current = eggs;
    egg_t *next = NULL;

    while (current != NULL) {
        next = current->next_tile;
        free(current);
        current = next;
    }
}
