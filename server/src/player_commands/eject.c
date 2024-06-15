/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** ejecting
*/

#include "server.h"

// Reject players from the tile
int eject_players(server_t *serv, client_t *player, int x, int y)
{
    int x2 = x;
    int y2 = y;
    int has_ejected = 0;

    if (player->orientation == NORTH)
        y2 = y_to_map_y(serv, y - 1);
    if (player->orientation == SOUTH)
        y2 = y_to_map_y(serv, y + 1);
    if (player->orientation == EAST)
        x2 = x_to_map_x(serv, x + 1);
    if (player->orientation == WEST)
        x2 = x_to_map_x(serv, x - 1);
    for (int i = 0; i < MAX_CLIENTS && serv->map[y][x].players[i]; i++)
        has_ejected += move_player(serv, serv->map[y][x].players[i], x2, y2);
    if (has_ejected > 0)
        event_pex(serv, player);
    return has_ejected;
}

// Push clients and break eggs in front of the player
int command_eject(server_t *serv, client_t *player, char *arg)
{
    int x = player->x;
    int y = player->y;

    if (arg != NULL)
        return 1;
    if (player->orientation == NORTH)
        y = y_to_map_y(serv, y - 1);
    if (player->orientation == SOUTH)
        y = y_to_map_y(serv, y + 1);
    if (player->orientation == EAST)
        x = x_to_map_x(serv, x + 1);
    if (player->orientation == WEST)
        x = x_to_map_x(serv, x - 1);
    if (player->orientation < 1 || player->orientation > 4)
        return 1;
    if (eject_players(serv, player, x, y) > 0 || serv->map[y][x].egg > 0) {
        serv->map[y][x].egg = 0;
        return success_response(player);
    }
    return 1;
}
