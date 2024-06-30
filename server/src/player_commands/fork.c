/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** forking
*/

#include "server.h"

// Create an egg
int command_fork(server_t *serv, client_t *player, char *arg)
{
    tile_t *tile = &serv->map[player->y][player->x];
    team_t *team = serv->teams[get_team_id(serv, player->team)];
    egg_t *egg = NULL;

    if (arg != NULL)
        return 1;
    egg = add_egg(team, tile);
    if (egg == NULL)
        return 1;
    team->free_slots++;
    event_enw(serv, player, egg);
    return success_response(player);
}
