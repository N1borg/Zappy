/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** incantation
*/

#include "../../include/main.h"

// Gives the number of players on the tile with the same level
int get_players(server_t *s, client_t *client)
{
    int x = client->x;
    int y = client->y;
    int level = client->level;
    int players = 0;

    for (int i = 0; i < MAX_CLIENTS && s->map[y][x].players[i]; i++) {
        if (s->map[y][x].players[i]->level == level)
            players++;
    }
    return players;
}

// Check if the player can incant for the last levels
int incant_lasts(server_t *s, client_t *client, tile_t *tile)
{
    int num_players = get_players(s, client);

    if (client->level == 6 && tile->linemate >= 1 &&
        tile->deraumere >= 2 && tile->sibur >= 3 &&
        tile->phiras >= 1 && num_players == 6) {
        dprintf(client->fd, "Current level: %d\n", client->level);
        return 0;
    }
    if (client->level == 7 && tile->linemate >= 2 && tile->deraumere >= 2
        && tile->sibur >= 2 && tile->mendiane >= 2 && tile->phiras >= 2 &&
        tile->mendiane >= 1 && num_players == 6) {
        dprintf(client->fd, "Current level: %d\n", client->level);
        return 0;
    }
    return 1;
}

// Check if the player can incant for the first levels
int incant_first(server_t *s, client_t *client, tile_t *tile)
{
    int num_players = get_players(s, client);

    if (client->level == 3 && tile->linemate >= 2 &&
        tile->sibur >= 1 && tile->phiras >= 2 &&
        num_players == 2) {
        dprintf(client->fd, "Current level: %d\n", client->level);
        return 0;
    }
    if (client->level == 4 && tile->linemate >= 1 && tile->deraumere >= 1
        && tile->sibur >= 2 && tile->phiras >= 1 && num_players == 4) {
        dprintf(client->fd, "Current level: %d\n", client->level);
        return 0;
    }
    if (client->level == 5 && tile->linemate >= 1 && tile->deraumere >= 2
        && tile->sibur >= 1 && tile->mendiane >= 3 && num_players == 4) {
        dprintf(client->fd, "Current level: %d\n", client->level);
        return 0;
    }
    return incant_lasts(s, client, tile);
}

// Check if the player can incant
int command_incantation(server_t *s, client_t *client, char *arg)
{
    int x = client->x;
    int y = client->y;
    int num_players = get_players(s, client);

    if (arg != NULL)
        return 1;
    if (client->level == 1 && s->map[y][x].linemate >= 1) {
        dprintf(client->fd, "Current level: %d\n", client->level);
        return 0;
    } else if (client->level == 2 && s->map[y][x].linemate >= 1 &&
        s->map[y][x].deraumere >= 1 && s->map[y][x].sibur >= 1
        && num_players == 2) {
        dprintf(client->fd, "Current level: %d\n", client->level);
        return 0;
    }
    return incant_first(s, client, &s->map[y][x]);
}
