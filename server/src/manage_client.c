/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** manage_client
*/

#include "server.h"

/* Accept a new client, print the New connection message and add it to
 the list of sockets */
void accept_client(server_t *serv)
{
    int addrlen = sizeof(serv->addr);
    int new_socket = accept(serv->master_socket,
    (struct sockaddr *)&serv->addr, (socklen_t *)&addrlen);

    if (new_socket < 0)
        perror("Accept");
    printf("[%d] - New connection | fd: %d, ip: %s, port: %d\n", new_socket,
    new_socket, inet_ntoa(serv->addr.sin_addr), ntohs(serv->addr.sin_port));
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (serv->clients[i]->fd == 0) {
            serv->clients[i]->fd = new_socket;
            init_command_queue(serv->clients[i]);
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
            s->map[client->y][client->x].players[get_player_id_on_map(
                &s->map[client->y][client->x], client)] = NULL;
        }
        s->teams[get_team_id(s, client->team)]->free_slots++;
    }
    close(client->fd);
    set_client(client);
}

// Initialize the client and send the map size and free slots
void init_player(server_t *serv, client_t *player)
{
    static int temp_id = 0;
    int team_id = get_team_id(serv, player->team);

    temp_id++;
    player->id = temp_id;
    dprintf(player->fd, "%d\n", serv->teams[team_id]->free_slots);
    dprintf(player->fd, "%d %d\n", serv->width, serv->height);
    event_pnw(serv, player);
}

// Create player if team_name exists else return 1
int create_player(server_t *serv, client_t *client, char *team_name)
{
    int x = rand() % serv->width;
    int y = rand() % serv->height;
    int i = 0;

    if (client->team != NULL || add_player_to_team(serv, client, team_name))
        return 1;
    for (; i < MAX_CLIENTS && serv->map[y][x].players[i]; i++);
    if (i == MAX_CLIENTS)
        return 1;
    client->id = 0;
    serv->map[y][x].players[i] = client;
    client->x = x;
    client->y = y;
    client->orientation = (rand() % 4) + 1;
    if (strcmp(team_name, "GRAPHIC") != 0)
        init_player(serv, client);
    return 0;
}
