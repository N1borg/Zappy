/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** broadcast
*/

#include "server.h"

// Sends a message to all players
int command_broadcast(server_t *serv, client_t *player, char *arg)
{
    if (arg == NULL)
        return 1;
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (serv->clients[i] && serv->clients[i]->team != NULL &&
            serv->clients[i]->id != player->id && serv->clients[i]->id != 0)
            dprintf(serv->clients[i]->fd, "message !!SET TILE!!, %s\n", arg);
    }
    event_pbc(serv, player, arg);
    return success_response(player);
}
