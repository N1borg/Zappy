/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** end of game
*/

#include "server.h"

// Send end game signal
void event_seg(server_t *serv, char *team)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (serv->clients[i] && serv->clients[i]->team &&
            strcmp(serv->clients[i]->team, "GRAPHIC") == 0) {
            dprintf(serv->clients[i]->fd, "seg %s\n", team);
        }
    }
}
