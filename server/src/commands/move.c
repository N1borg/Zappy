/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** moving
*/

#include "../../include/main.h"

// Move the client in the direction he is facing
int command_move_up(server_t *s, client_t *client)
{
    if (client->orientation == NORTH)
        move_player(s, client, client->x, client->y - 1);
    if (client->orientation == EAST)
        move_player(s, client, client->x + 1, client->y);
    if (client->orientation == SOUTH)
        move_player(s, client, client->x, client->y + 1);
    if (client->orientation == WEST)
        move_player(s, client, client->x - 1, client->y);
    printf("NEW POSITION: (%d,%d)|(%d,%d)\n", client->x, client->y,
        s->map[client->x][client->y].players[wich_player_on_map(s, client,
        client->x, client->y)]->x,
        s->map[client->x][client->y].players[wich_player_on_map(s,
        client, client->x, client->y)]->y,
        wich_player_on_map(s, client, client->x, client->y));
    if (client->orientation < 1 || client->orientation > 4)
        return 1;
    return 0;
}
