/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** handle_command
*/

#include "../include/main.h"

// Function to run command based on buffer, returns 1 on error
int run_command(server_t *s, client_t *client,
    char *buffer, struct CommandMap *command_map)
{
    for (int i = 0; buffer && command_map[i].command != NULL; i++) {
        if (strcmp(command_map[i].command, buffer) == 0
            && command_map[i].CommandFunction(s,
                client, strchr(buffer, ' ')) == 0)
            return 0;
    }
    return 1;
}

// Function to execute command based on buffer, returns 1 on error
int handle_command(server_t *s, client_t *client, char *buffer)
{
    struct CommandMap command_map[] = {{"Forward", command_move_up},
        {"Right", command_turn_right}, {"Left", command_turn_left},
        {"Look", command_look_around}, {"Inventory", command_inventory},
        {"Broadcast", command_broadcast}, {"Connect_nbr", command_team_slots},
        {"Fork", command_fork}, {"Eject", command_eject},
        {"Take object", command_take_object},
        {"Set object", command_set_object},
        {"Incantation", command_incantation},
        {NULL, NULL}};

    return run_command(s, client, buffer, command_map);
}

// Compute response based on buffer
void compute_response(server_t *s, client_t *client, char *buffer)
{
    printf("[%d] - sent: %s\n", client->fd, buffer);
    if (is_team(s, buffer) != 0) {
        if (create_player(s, client, buffer) == 0) {
            return;
        } else
            dprintf(client->fd, "ko\n");
    }
    if (client->team == NULL || handle_command(s, client, buffer))
        dprintf(client->fd, "ko\n");
}
