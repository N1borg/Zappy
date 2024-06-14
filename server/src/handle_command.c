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
    struct command_map command_map[] = {{"Forward", command_forward},
        {"Right", command_turn_right}, {"Left", command_turn_left},
        {"Look", command_look}, {"Inventory", command_inventory},
        {"Broadcast", command_broadcast}, {"Connect_nbr", command_team_slots},
        {"Fork", command_fork}, {"Eject", command_eject},
        {"Take object", command_take_object},
        {"Set object", command_set_object},
        {"Incantation", command_incantation},
        {NULL, NULL}};

    return run_command(s, client, buffer, command_map);
}

// Function to execute graphic command based on buffer, returns 1 on error
int handle_command_graphic(server_t *s, client_t *client, char *buffer)
{
    struct command_map command_map[] = {{"msz", command_msz},
        {"bct", command_bct}, {"mct", command_mct},
        {"tna", command_tna},
        {NULL, NULL}};

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
