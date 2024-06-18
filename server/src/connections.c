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
        if (valread == 0)
            disconnect_client(s, client);
        else {
            buffer[valread - 1] = '\0';
            printf("[%d] - sent: %s\n", client->fd, buffer);
            manage_queue(client, buffer);
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
    for (int i = 0; i < MAX_CLIENTS; i++) {
        (*sd) = s->clients[i]->fd;
        client_handler(s, s->clients[i]);
    }
    return 0;
}

// Execute the commands in the queue of the clients
void execute_queue(server_t *server)
{
    char *command = NULL;

    for (int i = 0; i < MAX_CLIENTS; i++) {
        command = dequeue_command(server->clients[i]->command_queue);
        if (command != NULL) {
            compute_response(server, server->clients[i], command);
            free(command);
        }
    }
}

// Start the server and listen for incoming connections
int start_listener(server_t *server)
{
    int sd = 0;
    int max_sd = 0;

    printf("Listening on port %d...\n", server->port);
    while (true) {
        if (listener_loop(server, &sd, &max_sd) != 0)
            return 84;
        execute_queue(server);
    }
    return 0;
}
