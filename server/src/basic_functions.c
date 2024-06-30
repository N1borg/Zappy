/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** basic_functions
*/

#include "server.h"

// Get the number of elements in a table
int tablen(team_t **tab)
{
    int i = 0;

    for (; tab && tab[i]; i++);
    return i;
}

// Return the index of the client in the tile, -1 in case of error
int get_player_id_on_map(tile_t *tile, client_t *player)
{
    if (player == NULL)
        return -1;
    for (int i = 0; i <= MAX_CLIENTS; i++) {
        if (tile->players[i] && tile->players[i]->id == player->id)
            return i;
    }
    return -1;
}

// Return 1 if team name exists, 0 if not
int is_team(server_t *serv, char *team_name)
{
    if (serv->teams == NULL)
        return 0;
    for (int i = 0; serv->teams[i] && serv->teams[i]->name; i++) {
        if (strcmp(team_name, serv->teams[i]->name) == 0)
            return 1;
    }
    return 0;
}

// Return 1 if socket exists as player, 0 if not
int is_player(server_t *serv, int socket)
{
    for (int i = 0; i < MAX_CLIENTS && serv->clients[i]; i++) {
        if (serv->clients[i]->fd == socket && serv->clients[i]->team != NULL)
            return 1;
    }
    return 0;
}

// Return the client based its id
client_t *get_client_by_id(server_t *serv, int id)
{
    for (int i = 0; i < MAX_CLIENTS && serv->clients[i]; i++) {
        if (serv->clients[i]->id == id)
            return serv->clients[i];
    }
    return NULL;
}
