/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** message from the server
*/

#include "server.h"

// Send a message to GRAPHIC clients
void event_smg(server_t *serv, char *msg)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (serv->clients[i] && serv->clients[i]->team &&
            strcmp(serv->clients[i]->team, "GRAPHIC") == 0) {
            dprintf(serv->clients[i]->fd, "smg %s\n", msg);
        }
    }
}
