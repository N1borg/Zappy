/*
** EPITECH PROJECT, 2024
** Zappy
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
