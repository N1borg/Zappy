/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** name of all the teams
*/

#include "server.h"

// Send the name of all the teams
int command_tna(server_t *serv, client_t *client, char *arg)
{
    if (arg != NULL)
        return event_sbp(client);
    for (int i = 0; serv->teams[i] != NULL
        && strcmp(serv->teams[i]->name, "GRAPHIC") != 0; i++) {
        dprintf(client->fd, "tna %s\n", serv->teams[i]->name);
    }
    return 0;
}
