/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** set_object
*/

#include "server.h"

// Drop object to inventory
int command_set_stones2(server_t *serv, client_t *player, char *arg)
{
    if (!strcmp(arg, "mendiane") && player->mendiane > 0) {
        player->mendiane--;
        serv->map[player->y][player->x].mendiane++;
        return success_response(player);
    }
    if (!strcmp(arg, "phiras") && player->phiras > 0) {
        player->phiras--;
        serv->map[player->y][player->x].phiras++;
        return success_response(player);
    }
    if (!!strcmp(arg, "thystame") && player->thystame > 0) {
        player->thystame--;
        serv->map[player->y][player->x].thystame++;
        return success_response(player);
    }
    return 1;
}

// Drop object to inventory
int command_set_stones1(server_t *serv, client_t *player, char *arg)
{
    if (!strcmp(arg, "linemate") && player->linemate > 0) {
        player->linemate--;
        serv->map[player->y][player->x].linemate++;
        return success_response(player);
    }
    if (!strcmp(arg, "deraumere") && player->deraumere > 0) {
        player->deraumere--;
        serv->map[player->y][player->x].deraumere++;
        return success_response(player);
    }
    if (!strcmp(arg, "sibur") && player->sibur > 0) {
        player->sibur--;
        serv->map[player->y][player->x].sibur++;
        return success_response(player);
    }
    return command_set_stones2(serv, player, arg);
}

// Drop object from inventory
int command_set_object(server_t *serv, client_t *player, char *arg)
{
    if (arg == NULL || strlen(arg) <= 3)
        return 1;
    arg++;
    if (!strcmp(arg, "food") && player->food > 0) {
        player->food--;
        serv->map[player->y][player->x].food++;
        return success_response(player);
    }
    return command_set_stones1(serv, player, arg);
}
