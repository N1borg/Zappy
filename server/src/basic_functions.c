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

// Return the index of the client in the map at the given position
int wich_player_on_map(server_t *s, client_t *client, int x, int y)
{
    for (int i = 0; i <= MAX_CLIENTS; i++) {
        if (s->map[x][y].players[i]
            && s->map[x][y].players[i]->fd == client->fd)
            return i;
    }
    return -1;
}

// Move the player to the given position based on the circular map
int move_player(server_t *s, client_t *client, int x, int y)
{
    int i = wich_player_on_map(s, client, client->x, client->y);
    int j = 0;

    if (i == -1)
        return 1;
    if (x < 0)
        x = s->width - 1;
    if (x >= s->width)
        x = 0;
    if (y < 0)
        y = s->height - 1;
    if (y >= s->height)
        y = 0;
    for (; j < MAX_CLIENTS && s->map[x][y].players[j]; j++);
    s->map[x][y].players[j] = client;
    s->map[client->x][client->y].players[i] = NULL;
    client->x = x;
    client->y = y;
    return 0;
}

// return 1 if team name exists, 0 if not and -1 in case of error
int is_team(server_t *s, char *team_name)
{
    if (s->teams == NULL)
        return -1;
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
