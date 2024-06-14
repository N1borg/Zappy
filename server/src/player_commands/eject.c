/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** ejecting
*/

#include "../../include/main.h"

// Reject players from the tile
int eject_players(server_t *s, client_t *client, int x, int y)
{
    int x2 = x;
    int y2 = y;
    int has_ejected = 0;

    if (client->orientation == NORTH)
        y2 = y_to_map_y(s, y - 1);
    if (client->orientation == SOUTH)
        y2 = y_to_map_y(s, y + 1);
    if (client->orientation == EAST)
        x2 = x_to_map_x(s, x + 1);
    if (client->orientation == WEST)
        x2 = x_to_map_x(s, x - 1);
    for (int i = 0; i < MAX_CLIENTS && s->map[y][x].players[i]; i++)
        has_ejected += move_player(s, s->map[y][x].players[i], x2, y2);
    return has_ejected;
}

// Push clients and break eggs in front of the player
int command_eject(server_t *s, client_t *client, char *arg)
{
    int x = client->x;
    int y = client->y;

    if (arg != NULL)
        return 1;
    if (client->orientation == NORTH)
        y = y_to_map_y(s, y - 1);
    if (client->orientation == SOUTH)
        y = y_to_map_y(s, y + 1);
    if (client->orientation == EAST)
        x = x_to_map_x(s, x + 1);
    if (client->orientation == WEST)
        x = x_to_map_x(s, x - 1);
    if (client->orientation < 1 || client->orientation > 4)
        return 1;
    if (eject_players(s, client, x, y) > 0 || s->map[y][x].egg > 0) {
        s->map[y][x].egg = 0;
        return success_response(client);
    }
    return 1;
}
