/*
** EPITECH PROJECT, 2023
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** ticks.c
*/

#include "server.h"

// Check if the player has a command in the queue
void check_player_queue(client_t *player, server_t *serv)
{
    if (player->tick == 0) {
        player->current_command = dequeue_command(player->command_queue);
        if (player->current_command == NULL) {
            player->tick = 0;
            return;
        }
    }
    player->tick++;
    if (player->tick >= player->current_command->time) {
        compute_response(serv, player, player->current_command->command);
        free(player->current_command->command);
        free(player->current_command);
        player->tick = 0;
    }
}

// Check if the player is dead
int check_player_death(server_t *serv, client_t *player)
{
    player->life -= 1;
    if (player->life >= 0)
        return 1;
    if (player->inv.food == 0) {
        event_pdi(serv, player);
        dprintf(player->fd, "dead\n");
        disconnect_client(serv, player);
        return 0;
    }
    player->inv.food--;
    player->life += 126;
    return 1;
}

void check_resource_event(server_t *serv)
{
    serv->refill -= 1;
    if (serv->refill <= 0) {
        generate_resources(serv);
        serv->refill += 20;
    }
}

// Elapse the time and check for player death
void elapse_time(server_t *serv, int *sd, struct timespec *start)
{
    struct timespec current;
    int elapsed_time;

    clock_gettime(CLOCK_REALTIME, &current);
    elapsed_time = (current.tv_sec - start->tv_sec) *
        1000000000 + (current.tv_nsec - start->tv_nsec);
    if (elapsed_time < 1000000000 / serv->freq)
        return;
    check_resource_event(serv);
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (serv->clients[i]->fd <= 0)
            continue;
        *sd = serv->clients[i]->fd;
        if (check_player_death(serv, serv->clients[i]) == 0)
            continue;
        client_handler(serv, serv->clients[i]);
        check_player_queue(serv->clients[i], serv);
    }
    start->tv_sec = current.tv_sec;
    start->tv_nsec = current.tv_nsec;
}
