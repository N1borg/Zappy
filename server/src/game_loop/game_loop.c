/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** game_loop.c
*/

#include "server.h"

// TODO: either parse command's name to know the time with the command structure
// or modify the command structure in .h to make it remember its command id and time
// we need a way to link the structures declared in scoped functions to functions in multiple files
// best solution is probably making the structures to be const structures in a separate .h

void consume_event(client_t *player, command_t *command)
{
    if (!command) {
        player->tick = 1;
        return;
    }
    player->tick = command->time;
}

void check_player_queue(client_t *player)
{
    command_t *command;

    player->tick -= 1;
    if (player->tick <= 0) {
        command = pop_queue(player->command_queue);
        consume_event(player, command);
    }
}

int check_player_death(client_t *player)
{
    player->life -= 1;
    if (player->life >= 0)
        return 1;
    if (!player->food) {
        dprintf(player->fd, "dead\n"); //TODO: add graphic 
        delete_client(player);
        return 0;
    }
    player->food -= 1;
    player->life += 126;
    return 1;
}

void elapse_time(server_t *serv)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (!serv->clients[i])
            continue;
        if (!check_player_death(serv->clients[i]))
            return;
        check_player_queue(serv->clients[i]);
    }
}

// TODO: change server->freq so that it is directly the number of 1000000000 / freq to avoid making a division every frame

int game_loop(server_t *serv)
{
    struct timespec start;
    struct timespec current;
    double elapsed_time = 0;

    clock_gettime(CLOCK_REALTIME, &start);
    while (!check_game_end(serv)) {
        select_client_commands(serv);
        clock_gettime(CLOCK_REALTIME, &current);
        elapsed_time = (current.tv_sec - start.tv_sec) * 1000000000 +
            (current.tv_nsec - start.tv_nsec);
        if (elapsed_time >= 1000000000 / serv->freq) {
            elapse_time(serv);
            start.tv_sec = current.tv_sec;
            start.tv_nsec = current.tv_nsec;
        }
    }

    return 84;
}
