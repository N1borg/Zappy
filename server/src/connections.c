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

// If the player has a command and the time is up, consume the event
void consume_event(server_t *serv, client_t *player, command_t *command)
{
    if (!command) {
        player->tick = 1;
        return;
    }
    player->tick = command->time;
    compute_response(serv, player, command->command, command->time);
    free(command->command);
    free(command);
}

// Check if the player has a command in the queue
void check_player_queue(client_t *player, server_t *serv)
{
    command_t *command = NULL;

    player->tick -= 1;
    if (player->tick <= 0) {
        command = dequeue_command(player->command_queue);
        consume_event(serv, player, command);
    }
}

// Check if the player is dead
int check_player_death(server_t *serv, client_t *player)
{
    player->life--;
    if (player->life >= 0)
        return 1;
    if (player->inv.food == 0) {
        event_pdi(serv, player);
        close(player->fd);
        return 0;
    }
    player->inv.food--;
    player->life += 126;
    return 1;
}

// Elapse the time and check for player death
void elapse_time(server_t *serv, int *sd)
{
    if (serv->elapsed_time < serv->interval)
        return;
    for (int i = 0; i < MAX_CLIENTS; i++) {
        *sd = serv->clients[i]->fd;
        if (serv->clients[i]->fd <= 0)
            continue;
        check_player_death(serv, serv->clients[i]);
            continue;
        client_handler(serv, serv->clients[i]);
        check_player_queue(serv->clients[i], serv);
    }
    serv->start.tv_sec = serv->current.tv_sec;
    serv->start.tv_nsec = serv->current.tv_nsec;
}

// Start the server and listen for incoming connections
void start_listener(server_t *serv)
{
    int sd = 0;
    int max_sd = 0;

    printf("Listening on port %d...\n", serv->port);
    clock_gettime(CLOCK_REALTIME, &serv->start);
    while (check_game_end(serv) == 0) {
        FD_ZERO(&serv->readfds);
        FD_SET(serv->master_socket, &serv->readfds);
        max_sd = serv->master_socket;
        add_child_socket(serv, &sd, &max_sd);
        if ((select((max_sd + 1), &serv->readfds, NULL, NULL, NULL) < 0)
            && (errno != EINTR))
            printf("Select error");
        if (FD_ISSET(serv->master_socket, &serv->readfds))
            accept_client(serv);
        clock_gettime(CLOCK_REALTIME, &serv->current);
        serv->elapsed_time = (serv->current.tv_sec - serv->start.tv_sec) *
            1000000000 + (serv->current.tv_nsec - serv->start.tv_nsec);
        elapse_time(serv, &sd);
    }
}
