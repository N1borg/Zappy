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
int incant_lasts(server_t *s, client_t *client, int x, int y)
{
    int num_players = get_players(s, client);

    if (client->level == 6 && s->map[y][x].linemate >= 1 &&
        s->map[y][x].deraumere >= 2 && s->map[y][x].sibur >= 3 &&
        s->map[y][x].phiras >= 1 && num_players == 6) {
        dprintf(client->fd, "Current level: %d\n", client->level);
        return 0;
    }
    if (client->level == 7 && s->map[y][x].linemate >= 2 &&
        s->map[y][x].deraumere >= 2 && s->map[y][x].sibur >= 2 &&
        s->map[y][x].mendiane >= 2 && s->map[y][x].phiras >= 2 &&
        s->map[y][x].mendiane >= 1 && num_players == 6) {
        dprintf(client->fd, "Current level: %d\n", client->level);
        return 0;
    }
    return 1;
}

// Check if the player can incant for the first levels
int incant_first(server_t *s, client_t *client, int x, int y, int num_players)
{
    if (client->level == 3 && s->map[y][x].linemate >= 2 &&
        s->map[y][x].sibur >= 1 && s->map[y][x].phiras >= 2 &&
        num_players == 2) {
        dprintf(client->fd, "Current level: %d\n", client->level);
        return 0;
    }
    if (client->level == 4 && s->map[y][x].linemate >= 1 &&
        s->map[y][x].deraumere >= 1 && s->map[y][x].sibur >= 2 &&
        s->map[y][x].phiras >= 1 && num_players == 4) {
        dprintf(client->fd, "Current level: %d\n", client->level);
        return 0;
    }
    if (client->level == 5 && s->map[y][x].linemate >= 1 &&
        s->map[y][x].deraumere >= 2 && s->map[y][x].sibur >= 1 &&
        s->map[y][x].mendiane >= 3 && num_players == 4) {
        dprintf(client->fd, "Current level: %d\n", client->level);
        return 0;
    }
    return incant_lasts(s, client, x, y);
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
    return incant_first(s, client, x, y, num_players);
}
