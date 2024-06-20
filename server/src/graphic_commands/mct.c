/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** content of the map (all the tiles)
*/

#include "server.h"

// Function to send the map content
int command_mct(server_t *serv, client_t *client, char *arg)
{
    if (arg != NULL)
        return event_sbp(client);
    for (int y = 0; y < serv->height; y++) {
        for (int x = 0; x < serv->width; x++)
            send_tile_content(serv, client, x, y);
    }
    return 0;
}
