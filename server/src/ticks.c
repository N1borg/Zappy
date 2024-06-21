/*
** EPITECH PROJECT, 2023
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** ticks.c
*/

#include "../include/server.h"

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
        compute_response(serv, player, command->command);
        free(command->command);
        free(command);
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
        if (serv->clients[i]->fd <= 0)
            continue;
        *sd = serv->clients[i]->fd;
        if (check_player_death(serv, serv->clients[i]) == 0)
            continue;
        client_handler(serv, serv->clients[i]);
        check_player_queue(serv->clients[i], serv);
    }
    serv->start.tv_sec = serv->current.tv_sec;
    serv->start.tv_nsec = serv->current.tv_nsec;
}
