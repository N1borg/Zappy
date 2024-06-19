/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** look_buffer_len
*/

#include "server.h"

// Return the number of chars to init the look buffer
int tile_size(tile_t *tile)
{
    int ret = 0;

    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (tile->players[i])
            ret += 7;
    }
    ret += ((get_nbr_eggs_on_tile(tile) * 4) + (tile->resources.food * 5)
    + (tile->resources.linemate * 9) + (tile->resources.deraumere * 10)
    + (tile->resources.sibur * 6) + (tile->resources.mendiane * 9)
    + (tile->resources.phiras * 7) + (tile->resources.thystame * 9));
    return (ret + 1);
}

// Return the number of chars to init the look buffer
int buffer_len(server_t *s, client_t *client)
{
    int n_char = 2;
    int loop = (client->orientation % 2);
    int vec = init_look(client, NULL);

    for (int i = 0; loop && i <= client->level; i++) {
        for (int j = 0; j < (i * 2 + 1); j++) {
            n_char += tile_size(&s->map[y_to_map_y(s, client->y + i * vec)]
                [x_to_map_x(s, client->x + ((j * -vec) + i * vec))]);
        }
    }
    for (int i = 0; !loop && i <= client->level; i++) {
        for (int j = 0; j < (i * 2 + 1); j++) {
            n_char += tile_size(
                &s->map[y_to_map_y(s, client->y - ((j * -vec) + i * vec))]
                [x_to_map_x(s, client->x + i * vec)]);
        }
    }
    return n_char;
}
