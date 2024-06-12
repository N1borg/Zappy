/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** map_size
*/

#include "../../include/main.h"

// Function to send the tile content
void send_tile_content(server_t *s, client_t *client, int x, int y)
{
    dprintf(client->fd, "bct %d %d %d %d %d %d %d %d %d\n", x, y,
        s->map[y][x].food, s->map[y][x].linemate, s->map[y][x].deraumere,
        s->map[y][x].sibur, s->map[y][x].mendiane, s->map[y][x].phiras,
        s->map[y][x].thystame);
}

// Function to send the tile content
int command_tile_content(server_t *s, client_t *client, char *arg)
{
    int x = atoi(strtok(arg, " "));
    int y = atoi(strtok(NULL, " "));

    if (x < 0 || x >= s->width || y < 0 || y >= s->height)
        return 1;
    send_tile_content(s, client, x, y);
    return 0;
}
