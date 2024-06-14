/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** content of a tile
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

// Return 1 if the string is an integer
int is_integer(const char *str)
{
    if (*str == '-' || *str == '+')
        str++;
    while (*str) {
        if (*str < '0' || *str > '9')
            return 0;
        str++;
    }
    return 1;
}

// Function to parse the command arguments
int parse_command_args(server_t *s, client_t *client,
    char *token, char *endptr)
{
    int x = 0;
    int y = 0;

    x = strtol(token, &endptr, 10);
    if (*endptr != '\0')
        return 1;
    token = strtok(NULL, " ");
    if (token == NULL || !is_integer(token))
        return 1;
    y = strtol(token, &endptr, 10);
    if (*endptr != '\0')
        return 1;
    token = strtok(NULL, " ");
    if (token != NULL)
        return 1;
    if (x < 0 || x >= s->width || y < 0 || y >= s->height)
        return 1;
    send_tile_content(s, client, x, y);
    return 0;
}

// Function to send the tile content
int command_bct(server_t *s, client_t *client, char *arg)
{
    char *token = NULL;
    char *endptr = NULL;

    if (arg == NULL)
        return 1;
    token = strtok(arg, " ");
    if (token == NULL || !is_integer(token))
        return 1;
    return parse_command_args(s, client, token, endptr);
}
