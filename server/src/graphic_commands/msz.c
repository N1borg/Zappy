/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** map_size
*/

#include "../../include/main.h"

// Function to send the map size to the client
int command_map_size(server_t *s, client_t *client,
    char *arg __attribute__((unused)))
{
    dprintf(client->fd, "msz %d %d\n", s->width, s->height);
    return 0;
}
