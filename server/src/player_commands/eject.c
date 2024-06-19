/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** ejecting
*/

#include "server.h"

// Calculate new coordinates based on orientation
void calculate_new_coordinates(server_t *serv, client_t *player, int *x, int *y)
{
    switch (player->orientation) {
        case NORTH:
            *y = y_to_map_y(serv, *y - 1);
            break;
        case SOUTH:
            *y = y_to_map_y(serv, *y + 1);
            break;
        case EAST:
            *x = x_to_map_x(serv, *x + 1);
            break;
        case WEST:
            *x = x_to_map_x(serv, *x - 1);
            break;
        default:
            break;
    }
}

// Reject players from the tile
int eject_players(server_t *serv, client_t *player, int x, int y)
{
    int x2 = x;
    int y2 = y;
    int has_ejected = 0;

    calculate_new_coordinates(serv, player, &x2, &y2);
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
    calculate_new_coordinates(serv, player, &x, &y);
    if (player->orientation < 1 || player->orientation > 4)
        return 1;
    if (eject_players(serv, player, x, y) > 0 ||
        destroy_eggs_from_tiles(&serv->map[y][x]) > 0)
        return success_response(player);
    return 1;
}
