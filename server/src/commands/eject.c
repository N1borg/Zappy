/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** ejecting
*/

#include "../../include/main.h"

// eject players from the tile
void eject_players(server_t *s, client_t *client, int x, int y)
{
    int x2 = x;
    int y2 = y;

    if (client->orientation == NORTH)
        y2 = ((y - 1) < 0) ? s->height - 1 : y - 1;
    if (client->orientation == SOUTH)
        y2 = ((y + 1) >= s->height) ? 0 : y + 1;
    if (client->orientation == EAST)
        x2 = ((x + 1) >= s->width) ? 0 : x + 1;
    if (client->orientation == WEST)
        x2 = ((x - 1) < 0) ? s->width - 1 : x - 1;
    for (int i = 0; i < MAX_CLIENTS && s->map[y][x].players[i]; i++)
        move_player(s, s->map[y][x].players[i], x2, y2);
}

// remove egg from the list
void remove_egg(egg_t **head, egg_t *egg)
{
    egg_t *current = NULL;

    if (head == NULL || *head == NULL || egg == NULL)
        return;
    if (*head == egg)
        *head = egg->next;
    else {
        current = *head;
        while (current->next != NULL && current->next != egg)
            current = current->next;
        if (current->next == egg)
            current->next = egg->next;
    }
}

// destroy eggs from the tile
void destroy_eggs(server_t *s, int x, int y)
{
    tile_t *tile = &s->map[y][x];
    egg_t *egg = tile->eggs;
    egg_t *next_egg = NULL;

    while (egg != NULL) {
        next_egg = egg->next;
        remove_egg(&s->eggs, egg);
        remove_egg(&egg->team->eggs, egg);
        remove_egg(&egg->client->eggs, egg);
        free(egg);
        egg = next_egg;
    }
    tile->eggs = NULL;
}

// push clients and break eggs in front of the player
int command_eject(server_t *s, client_t *client, char *arg)
{
    int x = client->x;
    int y = client->y;

    if (client->orientation == NORTH)
        y = ((y - 1) < 0) ? s->height - 1 : y - 1;
    if (client->orientation == SOUTH)
        y = ((y + 1) >= s->height) ? 0 : y + 1;
    if (client->orientation == EAST)
        x = ((x + 1) >= s->width) ? 0 : x + 1;
    if (client->orientation == WEST)
        x = ((x - 1) < 0) ? s->width - 1 : x - 1;
    eject_players(s, client, x, y);
    if destroy_eggs(s, x, y);
    return 0;
}
