/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** forking
*/

#include "../../include/main.h"

// create an egg
int command_fork(server_t *s, client_t *client,
    char *arg __attribute__((unused)))
{
    s->map[client->y][client->x].egg++;
    s->teams[which_team(s, client->team)]->free_slots++;
    return 0;
}
