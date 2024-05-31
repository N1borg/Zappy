/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** manage_client
*/

#include "../include/main.h"

/* Accept a new client, print the New connection message and add it to
 the list of sockets */
void accept_client(server_t *s)
{
    int addrlen = sizeof(s->addr);
    int new_socket = accept(s->master_socket,
    (struct sockaddr *)&s->addr, (socklen_t *)&addrlen);

    if (new_socket < 0)
        perror("Accept");
    printf("[%d] - New connection | fd: %d, ip: %s, port: %d\n", new_socket,
    new_socket, inet_ntoa(s->addr.sin_addr), ntohs(s->addr.sin_port));
    for (int i = 0; i < s->max_client_team; i++) {
        if (s->client_socket[i] == 0) {
            s->client_socket[i] = new_socket;
            printf("[%d] - Adding to list of sockets as %d\n", new_socket, i);
            break;
        }
    }
}

// Close the socket and print the disconnection message
void disconnect_client(server_t *s, int sd)
{
    int addrlen = sizeof(s->addr);

    getpeername(sd, (struct sockaddr *)&s->addr, (socklen_t *)&addrlen);
    printf("[%d] - Disconnected | ip: %s, port: %d \n", sd,
        inet_ntoa(s->addr.sin_addr), ntohs(s->addr.sin_port));
    close(sd);
}
