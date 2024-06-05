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

    if (init_socket(s) != 0 || init_listener(s) != 0)
        return 84;
    printf("Listening on port %d...\n", s->port);
    while (true) {
        if (listener_loop(s, &sd, &max_sd) != 0)
            return 84;
    }
    return 0;
}


// void display_map(server_t *s)
// {
//     for (int i = 0; i < s->height; i++) {
//         for (int j = 0; j < s->width; j++) {
//             printf("Tile (%d,%d) - Food: %d, Linemate: %d,
// Deraumere: %d, Sibur: %d, Mendiane: %d, Phiras: %d, Thystame: %d,
// Egg: %d", s->map[i][j].x,
// s->map[i][j].y, s->map[i][j].food, s->map[i][j].linemate,
// s->map[i][j].deraumere, s->map[i][j].sibur, s->map[i][j].mendiane,
// s->map[i][j].phiras, s->map[i][j].thystame, s->map[i][j].egg);
//             if (s->map[i][j].players[0] || s->map[i][j].players[1]) {
//                 for (int k = 0; k < MAX_CLIENTS; k++) {
//                     if (s->map[i][j].players[k])
//                         printf(" Player %d: x: %d, y: %d,
// level: %d, orientation: %d, team: %s", k, s->map[i][j].players[k]->x,
// s->map[i][j].players[k]->y, s->map[i][j].players[k]->level,
// s->map[i][j].players[k]->orientation, s->map[i][j].players[k]->team);
//                 }
//             }
//             printf("\n");
//         }
//     }
// }
