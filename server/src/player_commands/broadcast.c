/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** broadcast
*/

#include "../../include/main.h"

// Sends a message to all players
int command_broadcast(server_t *s, client_t *client, char *arg)
{
    if (arg == NULL)
        return 1;
    else
        arg++;
    for (int i = 0; s->clients[i]; i++) {
        if (s->clients[i]->fd != client->fd)
            dprintf(s->clients[i]->fd, "message !!SET TILE!!, %s\n", arg);
    }
    return success_response(client);
}
