/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** take_object
*/

#include "../../include/main.h"

// Take stone from map
int command_take_stones2(server_t *s, client_t *client, char *arg)
{
    if (!strcmp(arg, "mendiane") &&
            s->map[client->y][client->x].mendiane) {
        s->map[client->y][client->x].mendiane--;
        client->mendiane++;
        return success_response(client);
    }
    if (!strcmp(arg, "phiras") && s->map[client->y][client->x].phiras) {
        s->map[client->y][client->x].phiras--;
        client->phiras++;
        return success_response(client);
    }
    if (!strcmp(arg, "thystame") && s->map[client->y][client->x].thystame) {
        s->map[client->y][client->x].thystame--;
        client->thystame++;
        return success_response(client);
    }
    return 1;
}

// Take stone from map
int command_take_stones1(server_t *s, client_t *client, char *arg)
{
    if (!strcmp(arg, "linemate") && s->map[client->y][client->x].linemate) {
        s->map[client->y][client->x].linemate--;
        client->linemate++;
        return success_response(client);
    }
    if (!strcmp(arg, "deraumere") &&
        s->map[client->y][client->x].deraumere > 0) {
        s->map[client->y][client->x].deraumere--;
        client->deraumere++;
        return success_response(client);
    }
    if (!strcmp(arg, "sibur") && s->map[client->y][client->x].sibur) {
        s->map[client->y][client->x].sibur--;
        client->sibur++;
        return success_response(client);
    }
    return command_take_stones2(s, client, arg);
}

// Take object to inventory
int command_take_object(server_t *s, client_t *client, char *arg)
{
    if (arg == NULL || strlen(arg) <= 3)
        return 1;
    arg++;
    if (!strcmp(arg, "food") && s->map[client->y][client->x].food > 0) {
        s->map[client->y][client->x].food--;
        client->food++;
        return success_response(client);
    }
    return command_take_stones1(s, client, arg);
}
