/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** ejecting
*/

#include "../../include/main.h"

// eject players from the tile
void eject_players(server_t *s, client_t *client, int x, int y)
{
    int x2 = x;
    int y2 = y;

    switch (client->orientation) {
        case NORTH:
            y2 = ((y - 1) < 0) ? s->height - 1 : y - 1;
            break;
        case SOUTH:
            y2 = ((y + 1) >= s->height) ? 0 : y + 1;
            break;
        case EAST:
            x2 = ((x + 1) >= s->width) ? 0 : x + 1;
            break;
        case WEST:
            x2 = ((x - 1) < 0) ? s->width - 1 : x - 1;
            break;
    }
    for (int i = 0; i < MAX_CLIENTS && s->map[y][x].players[i]; i++)
        move_player(s, s->map[y][x].players[i], x2, y2);
}

// push clients and break eggs in front of the player
int command_eject(server_t *s, client_t *client, char *arg)
{
    int x = client->x;
    int y = client->y;

    switch (client->orientation) {
        case NORTH:
            y = ((y - 1) < 0) ? s->height - 1 : y - 1;
            break;
        case SOUTH:
            y = ((y + 1) >= s->height) ? 0 : y + 1;
            break;
        case EAST:
            x = ((x + 1) >= s->width) ? 0 : x + 1;
            break;
        case WEST:
            x = ((x - 1) < 0) ? s->width - 1 : x - 1;
            break;
    }
    eject_players(s, client, x, y);
    destroy_eggs_from_tiles(&s->map[y][x]);
    return 0;
}
