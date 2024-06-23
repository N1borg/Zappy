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
    command_map_t command_map[] = {
        {"Forward", command_forward, 7},
        {"Right", command_turn_right, 7},
        {"Left", command_turn_left, 7},
        {"Look", command_look, 7},
        {"Inventory", command_inventory, 1},
        {"Broadcast", command_broadcast, 7},
        {"Connect_nbr", command_team_slots, 0},
        {"Fork", command_fork, 42},
        {"Eject", command_eject, 7},
        {"Take", command_take_object, 7},
        {"Set", command_set_object, 7},
        {"Incantation", command_incantation, 300},
        {NULL, NULL, 0}
    };

    return run_command(serv, client, buffer, command_map);
}

// Function to execute graphic command based on buffer, returns 1 on error
int handle_command_graphic(server_t *serv, client_t *client, char *buffer)
{
    struct command_map command_map[] = {{"msz", command_msz, 0},
        {"bct", command_bct, 0}, {"mct", command_mct, 0},
        {"pin", command_pin, 0}, {"plv", command_plv, 0},
        {"ppo", command_ppo, 0}, {"sgt", command_sgt, 0},
        {"sst", command_sst, 0}, {"tna", command_tna, 0},
        {NULL, NULL, 0}};

    return run_command(serv, client, buffer, command_map);
}

// Compute response based on buffer
void compute_response(server_t *serv, client_t *client, char *buffer)
{
    if (is_team(serv, buffer) == 1) {
        if (init_client(serv, client, buffer) != 0
            && dprintf(client->fd, "ko\n") < 0 && errno == EPIPE)
                disconnect_client(serv, client);
        return;
    }
    if (client->team == NULL) {
        if (dprintf(client->fd, "ko\n") < 0 && errno == EPIPE)
            disconnect_client(serv, client);
        return;
    }
    if (strcmp(client->team, "GRAPHIC") != 0 &&
        handle_command_player(serv, client, buffer) != 0
        && dprintf(client->fd, "ko\n") < 0 && errno == EPIPE)
                disconnect_client(serv, client);
    if (strcmp(client->team, "GRAPHIC") == 0 &&
        handle_command_graphic(serv, client, buffer) != 0 &&
        dprintf(client->fd, "suc\n") < 0 && errno == EPIPE)
                disconnect_client(serv, client);
}
