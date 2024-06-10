/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** init_resource_pointers
*/

#include "server.h"

// Initialize the pointers to the resources on the map
void init_resource_pointers(tile_t *tile)
{
    resources[0].resource_ptr = &(tile->food);
    resources[1].resource_ptr = &(tile->linemate);
    resources[2].resource_ptr = &(tile->deraumere);
    resources[3].resource_ptr = &(tile->sibur);
    resources[4].resource_ptr = &(tile->mendiane);
    resources[5].resource_ptr = &(tile->phiras);
    resources[6].resource_ptr = &(tile->thystame);
}
