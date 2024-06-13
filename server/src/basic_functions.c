/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** basic_functions
*/

#include "../include/main.h"

// Get the number of elements in a table
int tablen(team_t **tab)
{
    int i = 0;

    for (; tab && tab[i]; i++);
    return i;
}

// Return the index of the client in the tile, -1 in case of error
int which_player_on_map(tile_t *tile, client_t *client)
{
    if (client == NULL)
        return -1;
    for (int i = 0; i <= MAX_CLIENTS; i++) {
        if (tile->players[i] && tile->players[i]->fd == client->fd)
            return i;
    }
    return -1;
}

// return 1 if team name exists, 0 if not
int is_team(server_t *s, char *team_name)
{
    if (s->teams == NULL)
        return 0;
    for (int i = 0; s->teams[i] && s->teams[i]->name; i++) {
        if (strcmp(team_name, s->teams[i]->name) == 0)
            return 1;
    }
    return 0;
}

// return 1 if socket exists as player, 0 if not
int is_player(server_t *s, int socket)
{
    for (int i = 0; s->clients[i]; i++) {
        if (s->clients[i]->fd == socket && s->clients[i]->team != NULL)
            return 1;
    }
    return 0;
}
