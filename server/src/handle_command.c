/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** handle_command
*/

#include "../include/main.h"

// Function to run command based on buffer, returns 1 on error
int run_command(server_t *s, client_t *client,
    char *buffer, struct command_map *command_map)
{
    char *args = strchr(buffer, ' ');
    char *command = NULL;

    if (args != NULL) {
        args = strdup(args + 1);
        command = strtok(buffer, " ");
    }
    if (command == NULL)
        command = buffer;
    printf("buffer: |%s|, command: |%s|, args: |%s|\n", buffer, command, args);
    for (int i = 0; command_map[i].command != NULL; i++) {
        if (strcmp(command_map[i].command, command) == 0) {
            return command_map[i].command_function(s,
                client, args);
        }
    }
    free(command);
    return 1;
}

// Function to execute player command based on buffer, returns 1 on error
int handle_command_player(server_t *s, client_t *client, char *buffer)
{
    struct command_map command_map[] = {
        {"Forward", command_forward, 7},
        {"Right", command_turn_right, 7},
        {"Left", command_turn_left, 7},
        {"Look", command_look, 7},
        {"Inventory", command_inventory, 1},
        {"Broadcast", command_broadcast, 7},
        {"Connect_nbr", command_team_slots, 0},
        {"Fork", command_fork, 42},
        {"Eject", command_eject, 7},
        {"Take object", command_take_object, 7},
        {"Set object", command_set_object, 7},
        {"Incantation", command_incantation, 300},
        {NULL, NULL, 0}
    };

    return run_command(s, client, buffer, command_map);
}

// Function to execute graphic command based on buffer, returns 1 on error
int handle_command_graphic(server_t *s, client_t *client, char *buffer)
{
    struct command_map command_map[] = {
        {"msz", command_map_size, 0},
        {"bct", command_tile_content, 0},
        {"mct", command_map_content, 0},
        {NULL, NULL, 0}
    };

    return run_command(s, client, buffer, command_map);
}


// Compute response based on buffer
void compute_response(server_t *s, client_t *client, char *buffer)
{
    if (is_team(s, buffer) == 1) {
        if (create_player(s, client, buffer) != 0)
            dprintf(client->fd, "ko\n");
        return;
    }
    if (client->team == NULL) {
        dprintf(client->fd, "ko\n");
        return;
    }
    printf("buffer: %s\n", buffer);
    if (strcmp(client->team, "GRAPHIC") != 0) {
        if (handle_command_player(s, client, buffer) != 0)
            dprintf(client->fd, "ko\n");
    }
    if (strcmp(client->team, "GRAPHIC") == 0) {
        if (handle_command_graphic(s, client, buffer) != 0)
            dprintf(client->fd, "ko\n");
    }
}
