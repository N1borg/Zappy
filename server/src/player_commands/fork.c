/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** forking
*/

#include "../../include/main.h"

// Create an egg
int command_fork(server_t *s, client_t *client, char *arg)
{
    if (arg != NULL)
        return 1;
    s->map[client->y][client->x].egg++;
    s->teams[get_team_id(s, client->team)]->free_slots++;
    return success_response(client);
}
