/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** command parameter
*/

#include "server.h"

// Send the `command parameter error` signal to the GRAPHIC client
int event_sbp(client_t *client)
{
    dprintf(client->fd, "sbp\n");
    return 0;
}
