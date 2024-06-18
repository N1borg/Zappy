/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** command_response
*/

#include "server.h"

// Send an ok response
int success_response(client_t *client)
{
    dprintf(client->fd, "ok\n");
    return 0;
}
