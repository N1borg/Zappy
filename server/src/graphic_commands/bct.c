/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** content of a tile
*/

#include "server.h"

/// @brief send to the GUI the content of a tile, using the map structure
/// @param serv server containing the map data
/// @param client the GUI client asking for the data, contains the target fd
/// @param x the position on the X-axis of the needed tile
/// @param y the position on the Y-axis of the needed tile
void send_tile_content(server_t *serv, client_t *client, int x, int y)
{
    dprintf(client->fd, "bct %d %d %d %d %d %d %d %d %d\n", x, y,
        serv->map[y][x].resources.food, serv->map[y][x].resources.linemate,
        serv->map[y][x].resources.deraumere, serv->map[y][x].resources.sibur,
        serv->map[y][x].resources.mendiane, serv->map[y][x].resources.phiras,
        serv->map[y][x].resources.thystame);
}

/// @brief check if a string is containing a number or not
/// @param str the string to check for a number
/// @return 1 for a number, 0 otherwise
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

/// @brief verifiy that the remaining argument contains two and only two
/// integer arguments for a position, and if they fit in the map size
/// @param serv server containing the main game data
/// @param client the GUI client asking for the data, contains the target fd
/// @param token the tokenized string, stripped of the command
/// @param endptr a pointer used to check if the string is finished
/// @return event_sbp() to GUI server if there is an error, nothing otherwise
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

/// @brief tile content function ask by GUI
/// @param serv server structure containing main game's data
/// @param client the client 
/// @param arg 
/// @return 
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
