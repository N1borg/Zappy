/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** forking
*/

#include "server.h"

// Create an egg
int command_fork(server_t *serv, client_t *client, char *arg)
{
    tile_t *tile = &serv->map[client->y][client->x];
    team_t *team = serv->teams[get_team_id(serv, client->team)];

    if (arg != NULL)
        return 1;
    if (add_egg(team, tile) == 84)
        return 84;
    team->free_slots++;
    return success_response(client);
}
