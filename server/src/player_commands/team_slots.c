/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** team_slots
*/

#include "../../include/main.h"

// Send the number of free slots in the team
int command_team_slots(server_t *s, client_t *client, char *arg)
{
    if (arg != NULL)
        return 1;
    dprintf(client->fd, "%d\n",
    s->teams[get_team_id(s, client->team)]->free_slots);
    return 0;
}
