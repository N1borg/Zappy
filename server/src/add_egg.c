/*
** EPITECH PROJECT, 2023
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** add_egg.c
*/

#include "../include/main.h"

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
    egg_t *current_tile = tile->eggs;

    if (current_tile == NULL) {
        tile->eggs = new_egg;
    } else {
        while (current_tile->next_tile != NULL) {
            current_tile = current_tile->next_tile;
        }
        current_tile->next_tile = new_egg;
    }
}

// Add an egg to the server
int add_egg(team_t *team, tile_t *tile)
{
    egg_t *new_egg = create_egg(team, tile);

    if (new_egg == NULL)
        return 84;
    add_egg_to_team(new_egg, team);
    add_egg_to_tile(new_egg, tile);
    return 0;
}
