/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** take_object
*/

#include "server.h"

// Take stone from map
int command_take_stones2(server_t *serv, client_t *player, char *arg)
{
    if (!strcmp(arg, "mendiane") &&
            serv->map[player->y][player->x].mendiane) {
        serv->map[player->y][player->x].mendiane--;
        player->mendiane++;
        return success_response(player);
    }
    if (!strcmp(arg, "phiras") && serv->map[player->y][player->x].phiras) {
        serv->map[player->y][player->x].phiras--;
        player->phiras++;
        return success_response(player);
    }
    if (!strcmp(arg, "thystame") && serv->map[player->y][player->x].thystame) {
        serv->map[player->y][player->x].thystame--;
        player->thystame++;
        return success_response(player);
    }
    return 1;
}

// Take stone from map
int command_take_stones1(server_t *serv, client_t *player, char *arg)
{
    if (!strcmp(arg, "linemate") && serv->map[player->y][player->x].linemate) {
        serv->map[player->y][player->x].linemate--;
        player->linemate++;
        return success_response(player);
    }
    if (!strcmp(arg, "deraumere") &&
        serv->map[player->y][player->x].deraumere > 0) {
        serv->map[player->y][player->x].deraumere--;
        player->deraumere++;
        return success_response(player);
    }
    if (!strcmp(arg, "sibur") && serv->map[player->y][player->x].sibur) {
        serv->map[player->y][player->x].sibur--;
        player->sibur++;
        return success_response(player);
    }
    return command_take_stones2(serv, player, arg);
}

// Take object to inventory
int command_take_object(server_t *serv, client_t *player, char *arg)
{
    if (arg == NULL || strlen(arg) <= 3)
        return 1;
    arg++;
    if (!strcmp(arg, "food") && serv->map[player->y][player->x].food > 0) {
        serv->map[player->y][player->x].food--;
        player->food++;
        return success_response(player);
    }
    return command_take_stones1(serv, player, arg);
}
