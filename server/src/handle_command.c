/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** handle_command
*/

#include "server.h"

// Function to run command based on buffer, returns 1 on error
int run_command(server_t *serv, client_t *client,
    char *buffer, command_map_t *command_map)
{
    char *args = strchr(buffer, ' ');
    char *command = NULL;

    if (args != NULL) {
        args = strdup(args + 1);
        command = strtok(buffer, " ");
    }
    if (command == NULL)
        command = buffer;
    for (int i = 0; command_map[i].command != NULL; i++) {
        if (strcmp(command_map[i].command, command) == 0) {
            return command_map[i].command_function(serv,
                client, args);
        }
    }
    return 1;
}

// Function to execute player command based on buffer, returns 1 on error
int handle_command_player(server_t *serv, client_t *client, char *buffer)
{
    command_map_t command_map[] = {{"Forward", command_forward},
        {"Right", command_turn_right}, {"Left", command_turn_left},
        {"Look", command_look}, {"Inventory", command_inventory},
        {"Broadcast", command_broadcast}, {"Connect_nbr", command_team_slots},
        {"Fork", command_fork}, {"Eject", command_eject},
        {"Take object", command_take_object},
        {"Set object", command_set_object},
        {"Incantation", command_incantation},
        {NULL, NULL}};

    return run_command(serv, client, buffer, command_map);
}

// Function to execute graphic command based on buffer, returns 1 on error
int handle_command_graphic(server_t *serv, client_t *client, char *buffer)
{
    struct command_map command_map[] = {{"msz", command_msz},
        {"bct", command_bct}, {"mct", command_mct},
        {"pin", command_pin}, {"plv", command_plv},
        {"ppo", command_ppo}, {"sgt", command_sgt},
        {"sst", command_sst}, {"tna", command_tna},
        {NULL, NULL}};

    return run_command(serv, client, buffer, command_map);
}

// Compute response based on buffer
void compute_response(server_t *serv, client_t *client, char *buffer)
{
    if (is_team(serv, buffer) == 1) {
        if (create_player(serv, client, buffer) != 0) {
            if (dprintf(client->fd, "ko\n") < 0 && errno == EPIPE)
                disconnect_client(serv, client);
        }
        return;
    }
    if (client->team == NULL) {
        if (dprintf(client->fd, "ko\n") < 0 && errno == EPIPE)
            disconnect_client(serv, client);
        return;
    }
    if (strcmp(client->team, "GRAPHIC") != 0 && handle_command_player(serv, client, buffer) != 0 && dprintf(client->fd, "ko\n") < 0 && errno == EPIPE)
                disconnect_client(serv, client);
    if (strcmp(client->team, "GRAPHIC") == 0 && handle_command_graphic(serv, client, buffer) != 0 && dprintf(client->fd, "ko\n") < 0 && errno == EPIPE)
                disconnect_client(serv, client);
}
