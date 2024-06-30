/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** coordinates
*/

#include "server.h"

// Convert the x position to the circular map
int x_to_map_x(server_t *serv, int x)
{
    int map_width = serv->width;

    x = x % map_width;
    if (x < 0)
        x += map_width;
    return x;
}

// Convert the y position to the circular map
int y_to_map_y(server_t *serv, int y)
{
    int map_height = serv->height;

    y = y % map_height;
    if (y < 0)
        y += map_height;
    return y;
}

// Move the player to the given position based on the circular map
int move_player(server_t *serv, client_t *client, int x, int y)
{
    int i = get_player_id_on_map(&serv->map[client->y][client->x], client);
    int j = 0;

    if (i == -1)
        return 0;
    x = x_to_map_x(serv, x);
    y = y_to_map_y(serv, y);
    for (; j < MAX_CLIENTS && serv->map[y][x].players[j]; j++);
    serv->map[y][x].players[j] = client;
    serv->map[client->y][client->x].players[i] = NULL;
    client->x = x;
    client->y = y;
    return 1;
}
