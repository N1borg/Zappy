/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** incantation
*/

#include "server.h"

// Gives the number of players on the tile with the same level
int get_players(server_t *serv, client_t *player)
{
    int x = player->x;
    int y = player->y;
    int level = player->level;
    int players = 0;

    for (int i = 0; i < MAX_CLIENTS && serv->map[y][x].players[i]; i++) {
        if (serv->map[y][x].players[i]->level == level)
            players++;
    }
    return players;
}

// Check if the player can incant for the last levels
int incant_lasts(server_t *serv, client_t *player, tile_t *tile)
{
    int num_players = get_players(serv, player);

    if (player->level == 6 && tile->linemate >= 1 &&
        tile->deraumere >= 2 && tile->sibur >= 3 &&
        tile->phiras >= 1 && num_players == 6) {
        dprintf(player->fd, "Current level: %d\n", player->level);
        return 0;
    }
    if (player->level == 7 && tile->linemate >= 2 && tile->deraumere >= 2
        && tile->sibur >= 2 && tile->mendiane >= 2 && tile->phiras >= 2 &&
        tile->mendiane >= 1 && num_players == 6) {
        dprintf(player->fd, "Current level: %d\n", player->level);
        return 0;
    }
    return 1;
}

// Check if the player can incant for the first levels
int incant_first(server_t *serv, client_t *player, tile_t *tile)
{
    int num_players = get_players(serv, player);

    if (player->level == 3 && tile->linemate >= 2 &&
        tile->sibur >= 1 && tile->phiras >= 2 &&
        num_players == 2) {
        dprintf(player->fd, "Current level: %d\n", player->level);
        return 0;
    }
    if (player->level == 4 && tile->linemate >= 1 && tile->deraumere >= 1
        && tile->sibur >= 2 && tile->phiras >= 1 && num_players == 4) {
        dprintf(player->fd, "Current level: %d\n", player->level);
        return 0;
    }
    if (player->level == 5 && tile->linemate >= 1 && tile->deraumere >= 2
        && tile->sibur >= 1 && tile->mendiane >= 3 && num_players == 4) {
        dprintf(player->fd, "Current level: %d\n", player->level);
        return 0;
    }
    return incant_lasts(serv, player, tile);
}

// Check if the player can incant
int command_incantation(server_t *serv, client_t *player, char *arg)
{
    int x = player->x;
    int y = player->y;
    int num_players = get_players(serv, player);

    if (arg != NULL)
        return 1;
    if (player->level == 1 && serv->map[y][x].linemate >= 1) {
        dprintf(player->fd, "Current level: %d\n", player->level);
        return 0;
    } else if (player->level == 2 && serv->map[y][x].linemate >= 1 &&
        serv->map[y][x].deraumere >= 1 && serv->map[y][x].sibur >= 1
        && num_players == 2) {
        dprintf(player->fd, "Current level: %d\n", player->level);
        return 0;
    }
    return incant_first(serv, player, &serv->map[y][x]);
}
