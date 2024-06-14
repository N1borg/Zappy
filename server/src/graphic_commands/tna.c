/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** name of all the teams
*/

#include "../../include/main.h"

// Send the name of all the teams
int command_tna(server_t *server, client_t *client, char *arg)
{
    if (arg != NULL)
        return 1;
    for (int i = 0; server->teams[i] != NULL; i++) {
        dprintf(client->fd, "tna %s\n", server->teams[i]->name);
    }
    return 0;
}
