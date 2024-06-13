/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** manage_client
*/

#include "../include/main.h"

// Return the index of the team in the server based on it's name
int which_team(server_t *s, char *team_name)
{
    for (int i = 0; s->teams[i] && s->teams[i]->name; i++) {
        if (strcmp(team_name, s->teams[i]->name) == 0)
            return i;
    }
    return -1;
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
    close(client->fd);
    client->fd = 0;
    s->map[client->y][client->x].players[
        which_player_on_map(&s->map[client->y][client->x], client)] = NULL;
    s->teams[which_team(s, client->team)]->free_slots++;
    set_client(client);
    add_egg(s->teams[which_team(s, client->team)], &s->map[client->y][client->x]);
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

// Get a random egg from a team
egg_t *get_random_egg(team_t *team)
{
    int count = 0;
    egg_t *current = team->eggs;
    int random_index = 0;

    for (; current != NULL; count++)
        current = current->next;
    if (count == 0)
        return NULL;
    random_index = rand() % count;
    current = team->eggs;
    for (int i = 0; i < random_index; i++)
        current = current->next;
    return current;
}

void destroy_eggs_tile(tile_t *tile)
{
    egg_t *egg = tile->eggs;
    egg_t *next_egg = NULL;

    while (egg != NULL) {
        next_egg = egg->next;
        remove_egg(&egg->team->eggs, egg);
        free(egg);
        egg = next_egg;
    }
    tile->eggs = NULL;
}

void destroy_egg(egg_t *egg)
{
    remove_egg(&egg->team->eggs, egg);
    remove_egg(&egg->tile->eggs, egg);
    free(egg);
}

// Set the position of a client based on the position of an egg
void set_client_pos(server_t *s, int *x, int *y, client_t *client)
{
    team_t *team = (*s).teams[which_team(s, (*client).team)];
    egg_t *egg = get_random_egg(team);

    *x = egg->tile->x;
    *y = egg->tile->y;
    destroy_egg(egg);
}

// create player if team_name exists else return 1
int create_player(server_t *s, client_t *client, char *team_name)
{
    int x = 0;
    int y = 0;
    int i = 0;

    if (client->team != NULL || add_player_to_team(s, client, team_name))
        return 1;
    set_client_pos(s, &x, &y, client);
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
