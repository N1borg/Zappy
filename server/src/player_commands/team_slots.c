/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** team_slots
*/

#include "../../include/main.h"

int command_team_slots(server_t *s, client_t *client,
    char *arg __attribute__((unused)))
{
    for (int i = 0; s->teams[i]; i++) {
        if (strcmp(s->teams[i]->name, client->team) == 0) {
            dprintf(client->fd, "%d\n", s->teams[i]->free_slots);
            return 0;
        }
    }
    return 1;
}
