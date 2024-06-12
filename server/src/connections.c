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
    for (int i = 0; i < s->max_client_team; i++) {
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
            compute_response(s, client, buffer);
        }
    }
}

// Main loop of the server
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

// Start the server and listen for incoming connections
int start_litener(server_t *s)
{
    int sd = 0;
    int max_sd = 0;
    clock_t last_tick = clock();
    double tick_interval = 1.0 / server->freq;
    clock_t current_time = 0;
    double elapsed_time = 0;

    if (init_socket(s) != 0 || init_listener(s) != 0)
        return 84;
    printf("Listening on port %d...\n", s->port);
    while (true) {
        current_time = clock();
        elapsed_time = (current_time - last_tick) / CLOCKS_PER_SEC;

        if (elapsed_time >= tick_interval) {
            handle_events();
            last_tick = current_time;
        }

        if (listener_loop(s, &sd, &max_sd) != 0)
            return 84;
    }
    return 0;
}
