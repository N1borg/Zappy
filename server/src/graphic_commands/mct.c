/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** mct
*/

#include "../../include/main.h"

// Function to send the map content
int command_map_content(server_t *s, client_t *client, char *arg)
{
    if (arg != NULL)
        return 1;
    for (int y = 0; y < s->height; y++) {
        for (int x = 0; x < s->width; x++)
            send_tile_content(s, client, x, y);
    }
    return 0;
}
