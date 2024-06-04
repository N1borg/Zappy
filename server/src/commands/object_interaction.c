/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** object_interaction
*/

#include "../../include/main.h"

// take object from inventory
int command_take_object2(server_t *s, client_t *client)
{
    if (s->map[client->y][client->x].sibur > 0) {
        s->map[client->y][client->x].sibur--;
        client->sibur++;
        return 0;
    } else if (s->map[client->y][client->x].mendiane > 0) {
        s->map[client->y][client->x].mendiane--;
        client->mendiane++;
        return 0;
    }
    if (s->map[client->y][client->x].phiras > 0) {
        s->map[client->y][client->x].phiras--;
        client->phiras++;
        return 0;
    } else if (s->map[client->y][client->x].thystame > 0) {
        s->map[client->y][client->x].thystame--;
        client->thystame++;
        return 0;
    }
    return 1;
}

// take object to inventory
int command_take_object(server_t *s, client_t *client)
{
    if (s->map[client->y][client->x].food > 0) {
        s->map[client->y][client->x].food--;
        client->food++;
        return 0;
    } else if (s->map[client->y][client->x].linemate > 0) {
        s->map[client->y][client->x].linemate--;
        client->linemate++;
        return 0;
    }
    if (s->map[client->y][client->x].deraumere > 0) {
        s->map[client->y][client->x].deraumere--;
        client->deraumere++;
        return 0;
    }
    return command_take_object2(s, client);
}

// drop object to inventory
int command_set_object2(server_t *s, client_t *client)
{
    if (client->mendiane > 0) {
        client->mendiane--;
        s->map[client->y][client->x].mendiane++;
        return 0;
    }
    if (client->phiras > 0) {
        client->phiras--;
        s->map[client->y][client->x].phiras++;
        return 0;
    }
    if (client->thystame > 0) {
        client->thystame--;
        s->map[client->y][client->x].thystame++;
        return 0;
    }
    return 1;
}

// drop object from inventory
int command_set_object(server_t *s, client_t *client)
{
    if (client->linemate > 0) {
        client->linemate--;
        s->map[client->y][client->x].linemate++;
        return 0;
    }
    if (client->deraumere > 0) {
        client->deraumere--;
        s->map[client->y][client->x].deraumere++;
        return 0;
    }
    if (client->sibur > 0) {
        client->sibur--;
        s->map[client->y][client->x].sibur++;
        return 0;
    }
    return command_set_object2(s, client);
}
