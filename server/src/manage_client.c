/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** manage_client
*/

#include "../include/main.h"

int create_graphic(server_t *s, client_t *client)
{
    if (client->team != NULL)
        return 1;
    client->team = strdup("GRAPHIC");
    dprintf(client->fd, "%d\n",
        s->teams[which_team(s, client->team)]->free_slots);
    dprintf(client->fd, "%d %d\n", s->width, s->height);
    return 0;
}

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
        if (s->clients[i]->fd == 0) {
            s->clients[i]->fd = new_socket;
            break;
        }
    }
    dprintf(new_socket, "WELCOME\n");
}

// Close the socket and print the disconnection message
void disconnect_client(server_t *s, client_t *client)
{
    int addrl = sizeof(s->addr);

    getpeername(client->fd, (struct sockaddr *)&s->addr, (socklen_t *)&addrl);
    printf("[%d] - Disconnected | ip: %s, port: %d \n", client->fd,
        inet_ntoa(s->addr.sin_addr), ntohs(s->addr.sin_port));
    if (client->team != NULL) {
        if (strcmp(client->team, "GRAPHIC") != 0) {
            s->map[client->y][client->x].players[which_player_on_map(
                &s->map[client->y][client->x], client)] = NULL;
        }
        s->teams[which_team(s, client->team)]->free_slots++;
    }
    close(client->fd);
    set_client(client);
}

// create player if team_name exists else return 1
int create_player(server_t *s, client_t *client, char *team_name)
{
    int x = 0;
    int y = 0;
    int i = 0;

    if (strcmp(team_name, "GRAPHIC") == 0)
        return create_graphic(s, client);
    if (client->team != NULL || add_player_to_team(s, client, team_name))
        return 1;
    x = rand() % s->width;
    y = rand() % s->height;
    for (; i < MAX_CLIENTS && s->map[y][x].players[i]; i++);
    if (i == MAX_CLIENTS)
        return 1;
    s->map[y][x].players[i] = client;
    client->x = x;
    client->y = y;
    client->orientation = (rand() % 4) + 1;
    dprintf(client->fd, "%d\n%d %d\n", s->teams[which_team(s,
        client->team)]->free_slots, s->width, s->height);
    return 0;
}
