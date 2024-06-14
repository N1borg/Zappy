/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** message from the server
*/

#include "../../include/main.h"

void event_smg(server_t *server, char *msg)
{
    for (int i = 0; server->clients[i] != NULL; i++) {
        if (strcmp(server->clients[i]->team, "GRAPHIC") == 0) {
            dprintf(server->clients[i]->fd, "smg %s\n", msg);
        }
    }
}
