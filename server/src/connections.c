/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** client handler
*/

#include "server.h"

// Add the child sockets to the readfds set
void add_child_socket(server_t *serv, int *sd, int *max_sd)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        (*sd) = serv->clients[i]->fd;
        if (*sd > 0)
            FD_SET(*sd, &serv->readfds);
        if (*sd > *max_sd)
            *max_sd = *sd;
    }
}

// Handle the client messages
void client_handler(server_t *serv, client_t *client)
{
    char buffer[1024];
    int valread = 0;

    if (FD_ISSET(client->fd, &serv->readfds)) {
        valread = read(client->fd, buffer, 1024);
        if (valread <= 0) {
            disconnect_client(serv, client);
        } else {
            buffer[valread - 1] = '\0';
            printf("[%d] - sent: %s\n", client->fd, buffer);
            manage_queue(client, buffer);
        }
    }
}

// Execute the commands in the queue of the clients
void execute_queue(server_t *serv, client_t *client)
{
    command_t *command  = dequeue_command(client->command_queue);

    if (command != NULL) {
        compute_response(serv, client, command->command, command->time);
        free(command->command);
        free(command);
    }
}

// Start the server and listen for incoming connections
void start_listener(server_t *serv)
{
    int sd = 0;
    int max_sd = 0;

    printf("Listening on port %d...\n", serv->port);
    while (true) {
        FD_ZERO(&serv->readfds);
        FD_SET(serv->master_socket, &serv->readfds);
        max_sd = serv->master_socket;
        add_child_socket(serv, &sd, &max_sd);
        if ((select((max_sd + 1), &serv->readfds, NULL, NULL, NULL) < 0)
            && (errno != EINTR))
            printf("Select error");
        if (FD_ISSET(serv->master_socket, &serv->readfds))
            accept_client(serv);
        for (int i = 0; i < MAX_CLIENTS; i++) {
            sd = serv->clients[i]->fd;
            client_handler(serv, serv->clients[i]);
            execute_queue(serv, serv->clients[i]);
        }
    }
}
