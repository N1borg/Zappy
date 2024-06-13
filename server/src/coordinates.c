/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** coordinates
*/

#include "../include/main.h"

// Convert the x position to the circular map
int x_to_map_x(server_t *s, int x)
{
    int map_width = s->width;

    x = x % map_width;
    if (x < 0)
        x += map_width;
    return x;
}

// Convert the y position to the circular map
int y_to_map_y(server_t *s, int y)
{
    int map_height = s->height;

    y = y % map_height;
    if (y < 0)
        y += map_height;
    return y;
}

// Move the player to the given position based on the circular map
int move_player(server_t *s, client_t *client, int x, int y)
{
    int i = get_player_id_on_map(&s->map[client->y][client->x], client);
    int j = 0;

    if (i == -1)
        return 0;
    x = x_to_map_x(s, x);
    y = y_to_map_y(s, y);
    for (; j < MAX_CLIENTS && s->map[y][x].players[j]; j++);
    s->map[y][x].players[j] = client;
    s->map[client->y][client->x].players[i] = NULL;
    client->x = x;
    client->y = y;
    return 1;
}
