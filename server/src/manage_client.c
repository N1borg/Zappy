/*
** EPITECH PROJECT, 2024
** Zappy
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
void disconnect_client(server_t *serv, client_t *client)
{
    int addrl = sizeof(serv->addr);

    getpeername(client->fd,
        (struct sockaddr *)&serv->addr, (socklen_t *)&addrl);
    printf("[%d] - Disconnected | ip: %s, port: %d \n", client->fd,
        inet_ntoa(serv->addr.sin_addr), ntohs(serv->addr.sin_port));
    if (client->team != NULL) {
        if (strcmp(client->team, "GRAPHIC") != 0) {
            event_pdi(serv, client);
            serv->map[client->y][client->x].players[get_player_id_on_map(
                &serv->map[client->y][client->x], client)] = NULL;
        }
    }
    close(client->fd);
    set_client(client);
}

// Get a random egg from a team
static egg_t *get_random_egg(team_t *team)
{
    int count = 0;
    egg_t *current = team->eggs;
    int random_index = 0;

    for (; current != NULL; count++)
        current = current->next_team;
    if (count <= 0)
        return NULL;
    random_index = rand() % count;
    current = team->eggs;
    for (int i = 0; i < random_index; i++)
        current = current->next_team;
    return current;
}

// Initialize the client and send the map size and free slots
void init_player(server_t *serv, client_t *player)
{
    static int temp_id = 0;
    int team_id = get_team_id(serv, player->team);
    team_t *team = serv->teams[team_id];
    egg_t *egg = get_random_egg(team);

    if (egg == NULL) {
        disconnect_client(serv, player);
        return;
    }
    player->orientation = (rand() % 4) + 1;
    player->x = egg->tile->x;
    player->y = egg->tile->y;
    remove_egg(egg);
    temp_id++;
    player->id = temp_id;
    event_pnw(serv, player);
    dprintf(player->fd, "%d\n", serv->teams[team_id]->free_slots);
    dprintf(player->fd, "%d %d\n", serv->width, serv->height);
}

// Initialize a client
int init_client(server_t *serv, client_t *client, char *team_name)
{
    int i = 0;

    if (client->team != NULL)
        return 1;
    if (strcmp(team_name, "GRAPHIC") == 0 && add_graphic_to_team(serv, client))
            return 1;
    if (strcmp(team_name, "GRAPHIC") != 0) {
        if (add_player_to_team(serv, client, team_name))
            return 1;
        for (; i < MAX_CLIENTS &&
            serv->map[client->y][client->x].players[i]; i++);
        if (i == MAX_CLIENTS)
            return 1;
        init_player(serv, client);
        serv->map[client->y][client->x].players[i] = client;
    }
    return 0;
}
