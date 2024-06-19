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

// Incant all players on the tile with the same level
int incant_all_players(server_t *serv, client_t *player)
{
    int x = player->x;
    int y = player->y;
    int level = player->level;
    int players_to_evolve = (((level + 1) / 2) * 2);
    printf("players_to_evolve: %d\n", players_to_evolve);
    int players_evolved = 0;

    player->is_incanting = false;
    for (int i = 0; players_evolved < level
        && i < MAX_CLIENTS && serv->map[y][x].players[i]; i++) {
        if (serv->map[y][x].players[i]->level == level) {
            players_evolved++;
            serv->map[y][x].players[i]->level++;
            dprintf(serv->map[y][x].players[i]->fd,
            "Current level: %d\n", serv->map[y][x].players[i]->level);
        }
    }
    return 0;
}

// Check if the player can incant for the last levels
int incant_lasts(server_t *serv, client_t *player, tile_t *tile)
{
    int num_players = get_players(serv, player);

    if (player->level == 6 && tile->linemate >= 1 &&
        tile->deraumere >= 2 && tile->sibur >= 3 &&
        tile->phiras >= 1 && num_players == 6)
        return incant_all_players(serv, player);
    if (player->level == 7 && tile->linemate >= 2 && tile->deraumere >= 2
        && tile->sibur >= 2 && tile->mendiane >= 2 && tile->phiras >= 2 &&
        tile->mendiane >= 1 && num_players == 6)
        return incant_all_players(serv, player);
    return 1;
}

// Check if the player can incant for the first levels
int incant_first(server_t *serv, client_t *player, tile_t *tile)
{
    int num_players = get_players(serv, player);

    if (player->level == 3 && tile->linemate >= 2 &&
        tile->sibur >= 1 && tile->phiras >= 2 &&
        num_players == 2)
        return incant_all_players(serv, player);
    if (player->level == 4 && tile->linemate >= 1 && tile->deraumere >= 1
        && tile->sibur >= 2 && tile->phiras >= 1 && num_players == 4)
        return incant_all_players(serv, player);
    if (player->level == 5 && tile->linemate >= 1 && tile->deraumere >= 2
        && tile->sibur >= 1 && tile->mendiane >= 3 && num_players == 4)
        return incant_all_players(serv, player);
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
    if (player->level == 1 && serv->map[y][x].linemate >= 1)
        return incant_all_players(serv, player);
    if (player->level == 2 && serv->map[y][x].linemate >= 1 &&
        serv->map[y][x].deraumere >= 1 && serv->map[y][x].sibur >= 1
        && num_players == 2)
        return incant_all_players(serv, player);
    return incant_first(serv, player, &serv->map[y][x]);
}
