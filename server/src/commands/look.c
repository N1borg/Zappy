/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** looking
*/

#include "../../include/main.h"

// sends the content of the map in front of the client
int command_look_around(server_t *s, client_t *client)
{
    dprintf(client->fd, "AROUND\n");
    return 0;
}
