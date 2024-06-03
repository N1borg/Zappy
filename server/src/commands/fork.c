/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** forking
*/

#include "../../include/main.h"

// create an egg
int command_fork(server_t *s, client_t *client)
{
    s->map[client->x][client->y].egg++;
    return 0;
}
