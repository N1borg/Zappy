/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** unknown command
*/

#include "server.h"

// jsp
void event_suc(client_t *client)
{
    dprintf(client->fd, "suc\n");
}