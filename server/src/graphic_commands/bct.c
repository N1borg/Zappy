/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** content of a tile
*/

#include "server.h"

// Function to send the tile content
void send_tile_content(server_t *serv, client_t *client, int x, int y)
{
    dprintf(client->fd, "bct %d %d %d %d %d %d %d %d %d\n", x, y,
        serv->map[y][x].resources.food, serv->map[y][x].resources.linemate,
        serv->map[y][x].resources.deraumere, serv->map[y][x].resources.sibur,
        serv->map[y][x].resources.mendiane, serv->map[y][x].resources.phiras,
        serv->map[y][x].resources.thystame);
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
int parse_command_args(server_t *serv, client_t *client,
    char *token, char *endptr)
{
    int x = 0;
    int y = 0;

    x = strtol(token, &endptr, 10);
    if (*endptr != '\0')
        return event_sbp(client);
    token = strtok(NULL, " ");
    if (token == NULL || !is_integer(token))
        return event_sbp(client);
    y = strtol(token, &endptr, 10);
    if (*endptr != '\0')
        return event_sbp(client);
    token = strtok(NULL, " ");
    if (token != NULL)
        return event_sbp(client);
    if (x < 0 || x >= serv->width || y < 0 || y >= serv->height)
        return event_sbp(client);
    send_tile_content(serv, client, x, y);
    return 0;
}

// Function to send the tile content
int command_bct(server_t *serv, client_t *client, char *arg)
{
    char *token = NULL;
    char *endptr = NULL;

    if (arg == NULL)
        return event_sbp(client);
    token = strtok(arg, " ");
    if (token == NULL || !is_integer(token))
        return event_sbp(client);
    return parse_command_args(serv, client, token, endptr);
}
