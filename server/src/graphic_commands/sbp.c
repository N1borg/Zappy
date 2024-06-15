/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** command parameter
*/

#include "server.h"

// jsp
void event_sbp(client_t *client)
{
    dprintf(client->fd, "sbp\n");
}
