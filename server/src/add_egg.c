/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** add_egg.c
*/

#include "server.h"

// Get the number of eggs on a tile
int get_nbr_eggs_on_tile(tile_t *tile)
{
    egg_t *current = tile->eggs;
    int count = 0;

    while (current != NULL) {
        count += 1;
        current = current->next_tile;
    }
    return count;
}

// Create the node for the new egg
egg_t *create_egg(team_t *team, tile_t *tile)
{
    static int next_id = 0;
    egg_t *new_egg = malloc(sizeof(egg_t));

    if (new_egg == NULL)
        return NULL;
    new_egg->tile = tile;
    new_egg->team = team;
    new_egg->id = next_id;
    next_id += 1;
    new_egg->next_team = NULL;
    new_egg->next_tile = NULL;
    return new_egg;
}

// Add the egg to the team
void add_egg_to_team(egg_t *new_egg, team_t *team)
{
    egg_t *current_team = team->eggs;

    if (current_team == NULL) {
        team->eggs = new_egg;
    } else {
        while (current_team->next_team != NULL) {
            current_team = current_team->next_team;
        }
        current_team->next_team = new_egg;
    }
}

// Add the egg to the tile
void add_egg_to_tile(egg_t *new_egg, tile_t *tile)
{
    egg_t *current_tile = NULL;

    if (tile == NULL || new_egg == NULL)
        return;
    if (tile->eggs == NULL) {
        tile->eggs = new_egg;
    } else {
        current_tile = tile->eggs;
        while (current_tile->next_tile != NULL) {
            current_tile = current_tile->next_tile;
        }
        current_tile->next_tile = new_egg;
    }
}

// Add an egg to the server
egg_t *add_egg(team_t *team, tile_t *tile)
{
    egg_t *new_egg = create_egg(team, tile);

    if (new_egg == NULL)
        return NULL;
    add_egg_to_team(new_egg, team);
    add_egg_to_tile(new_egg, tile);
    return new_egg;
}
