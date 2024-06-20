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
        serv->teams[get_team_id(serv, client->team)]->free_slots++;
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

// Get a random egg from a team
static egg_t *get_random_egg(team_t *team)
{
    int count = 0;
    egg_t *current = team->eggs;
    int random_index = 0;

    for (; current != NULL; count++)
        current = current->next_team;
    random_index = rand() % count;
    current = team->eggs;
    for (int i = 0; i < random_index; i++)
        current = current->next_team;
    return current;
}

// Set the position of a client based on the position of an egg
static void set_client_pos(server_t *s, client_t *client)
{
    team_t *team = (*s).teams[get_team_id(s, (*client).team)];
    egg_t *egg = get_random_egg(team);

    client->x = egg->tile->x;
    client->y = egg->tile->y;
    remove_egg(egg);
}

// create player if team_name exists else return 1
int create_player(server_t *s, client_t *client, char *team_name)
{
    int i = 0;

    if (client->team != NULL || add_player_to_team(s, client, team_name))
        return 1;
    for (; i < MAX_CLIENTS && s->map[client->y][client->x].players[i]; i++);
    if (i == MAX_CLIENTS)
        return 1;
    set_client_pos(s, client);
    s->map[client->y][client->x].players[i] = client;
    client->orientation = (rand() % 4) + 1;
    dprintf(client->fd, "%d\n",
        s->teams[get_team_id(s, client->team)]->free_slots);
    dprintf(client->fd, "%d %d\n", s->width, s->height);
    return 0;
}
