/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** end of an incantation
*/

#include "server.h"

// Send the end of an incantation signal to GRAPHIC clients
void event_pie(server_t *serv, client_t *player, char *result)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (serv->clients[i] && serv->clients[i]->team &&
            strcmp(serv->clients[i]->team, "GRAPHIC") == 0) {
            dprintf(serv->clients[i]->fd, "pie %d %d %s\n",
                player->x, player->y, result);
        }
    }
}
