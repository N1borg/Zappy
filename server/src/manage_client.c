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
    close(client->fd);
    client->fd = 0;
    s->map[client->y][client->x].players[
        which_player_on_map(s, client, client->x, client->y)] = NULL;
    set_client(client);
    s->teams[which_team(s, client->team)]->free_slots++;
}

// Add a player to a team based on it's name
int add_player_to_team(server_t *s, client_t *player, char *team_name)
{
    int i = 0;
    int j = 0;

    if (player == NULL || team_name == NULL)
        return 1;
    for (; s->teams[i] && strcmp(team_name, s->teams[i]->name); i++);
    if (s->teams[i] && s->teams[i]->free_slots >= 1
        && strcmp(team_name, s->teams[i]->name) == 0) {
        for (; j < MAX_CLIENTS && s->teams[i]->players[j]; j++);
        if (j < MAX_CLIENTS) {
            s->teams[i]->players[j] = player;
            player->team = s->teams[i]->name;
            player->level = 1;
            s->teams[i]->free_slots--;
        } else
            return 1;
    } else
        return 1;
    return 0;
}

// Return the index of the team in the server based on it's name
int which_team(server_t *s, char *team_name)
{
    for (int i = 0; s->teams[i] && s->teams[i]->name; i++) {
        if (strcmp(team_name, s->teams[i]->name) == 0)
            return i;
    }
    return -1;
}

// create player if team_name exists else return 1
int create_player(server_t *s, client_t *client, char *team_name)
{
    int x = 0;
    int y = 0;
    int i = 0;

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
    dprintf(client->fd, "%d\n",
        s->teams[which_team(s, client->team)]->free_slots);
    dprintf(client->fd, "%d %d\n", s->width, s->height);
    return 0;
}
