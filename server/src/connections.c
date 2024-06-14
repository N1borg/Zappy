/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** client handler
*/

#include "../include/main.h"

// Add the child sockets to the readfds set
void add_child_socket(server_t *s, int *sd, int *max_sd)
{
    for (int i = 0; i < s->max_client_team * s->team_nb; i++) {
        (*sd) = s->clients[i]->fd;
        if (*sd > 0)
            FD_SET(*sd, &s->readfds);
        if (*sd > *max_sd)
            *max_sd = *sd;
    }
}

// Handle the client messages
void client_handler(server_t *s, client_t *client)
{
    char buffer[1024];
    int valread = 0;

    if (FD_ISSET(client->fd, &s->readfds)) {
        valread = read(client->fd, buffer, 1024);
        if (valread == 0) {
            disconnect_client(s, client);
        } else {
            buffer[valread - 1] = '\0';
            printf("[%d] - sent: %s\n", client->fd, buffer);
            if (enqueue_command(client, buffer) == 1)   
                dprintf(client->fd, "Command queue is full\n");
            else
                dprintf(client->fd, "Command %s enqueued\n", buffer);
            printf("Command queue is full\n");
        }
    }
}

// Execute command from the client's command queue
void execute_client_commands(server_t *s, client_t *client)
{
    char *command = dequeue_command(client->command_queue);

    compute_response(s, client, command);
    free(command);
}

// Handle all client commands
void handle_client_commands(server_t *s, int *sd)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        (*sd) = s->clients[i]->fd;
        if (s->clients[i] != NULL) {
            client_handler(s, s->clients[i]);
            execute_client_commands(s, s->clients[i]);
        }
    }
}

// Handle the client commands
int listener_loop(server_t *s, int *sd, int *max_sd)
{
    FD_ZERO(&s->readfds);
    FD_SET(s->master_socket, &s->readfds);
    *max_sd = s->master_socket;
    add_child_socket(s, sd, max_sd);
    if ((select(*max_sd + 1, &s->readfds, NULL, NULL, NULL) < 0)
        && (errno != EINTR))
        printf("Select error");
    if (FD_ISSET(s->master_socket, &s->readfds))
        accept_client(s);
    handle_client_commands(s, sd);
    return 0;
}

// Start the server and listen for incoming connections
int start_listener(server_t *s)
{
    int sd = 0;
    int max_sd = 0;

    printf("Listening on port %d...\n", s->port);
    while (true) {
        if (listener_loop(s, &sd, &max_sd) != 0)
            return 84;
    }
    return 0;
}
