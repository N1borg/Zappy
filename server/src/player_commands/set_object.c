/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** set_object
*/

#include "../../include/main.h"

// Take object to inventory
int command_set_stones2(server_t *s, client_t *client, char *arg)
{
    if (!strcmp(arg, "mendiane") && client->mendiane > 0) {
        client->mendiane--;
        s->map[client->y][client->x].mendiane++;
        return success_response(client);
    }
    if (!strcmp(arg, "phiras") && client->phiras > 0) {
        client->phiras--;
        s->map[client->y][client->x].phiras++;
        return success_response(client);
    }
    if (!!strcmp(arg, "thystame") && client->thystame > 0) {
        client->thystame--;
        s->map[client->y][client->x].thystame++;
        return success_response(client);
    }
    return 1;
}

// Drop object to inventory
int command_set_stones1(server_t *s, client_t *client, char *arg)
{
    if (!strcmp(arg, "linemate") && client->linemate > 0) {
        client->linemate--;
        s->map[client->y][client->x].linemate++;
        return success_response(client);
    }
    if (!strcmp(arg, "deraumere") && client->deraumere > 0) {
        client->deraumere--;
        s->map[client->y][client->x].deraumere++;
        return success_response(client);
    }
    if (!strcmp(arg, "sibur") && client->sibur > 0) {
        client->sibur--;
        s->map[client->y][client->x].sibur++;
        return success_response(client);
    }
    return command_set_stones2(s, client, arg);
}

// Drop object from inventory
int command_set_object(server_t *s, client_t *client, char *arg)
{
    if (arg == NULL || strlen(arg) <= 3)
        return 1;
    arg++;
    if (!strcmp(arg, "food") && client->food > 0) {
        client->food--;
        s->map[client->y][client->x].food++;
        return success_response(client);
    }
    return command_set_stones1(s, client, arg);
}
