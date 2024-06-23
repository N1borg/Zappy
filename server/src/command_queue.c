/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** command_queue.c
*/

#include "server.h"

// Initialize the command queue of the client
void init_command_queue(client_t *client)
{
    client->command_queue = malloc(sizeof(command_queue_t));
    if (client->command_queue == NULL)
        return;
    client->command_queue->front = NULL;
    client->command_queue->back = NULL;
    client->command_queue->size = 0;
}

// Get the time of a command
static int get_command_time(char *command_str, command_time_t *command_time)
{
    for (int i = 0; command_time[i].command != NULL; i++) {
        if (strcmp(command_str, command_time[i].command) == 0)
            return command_time[i].time_limit;
    }
    return 0;
}

// Enqueue a command in the command queue of the client
static int add_command(client_t *client, char *command_str,
    command_time_t *command_time)
{
    command_t *new_command = NULL;

    new_command = malloc(sizeof(command_t));
    if (new_command == NULL)
        return 84;
    new_command->command = strdup(command_str);
    new_command->time = get_command_time(command_str, command_time);
    if (new_command->command == NULL) {
        free(new_command);
        return 84;
    }
    new_command->next = NULL;
    if (client->command_queue->back == NULL) {
        client->command_queue->front = new_command;
        client->command_queue->back = new_command;
    } else {
        client->command_queue->back->next = new_command;
        client->command_queue->back = new_command;
    }
    client->command_queue->size++;
    return 0;
}

int enqueue_command(client_t *client, char *command_str)
{
    command_time_t command_time[] = {
        {"Forward", 7},
        {"Right", 7},
        {"Left", 7},
        {"Look", 7},
        {"Inventory", 1},
        {"Broadcast", 7},
        {"Connect_nbr", 0},
        {"Fork", 42},
        {"Eject", 7},
        {"Take", 7},
        {"Set", 7},
        {"Incantation", 300},
        {NULL, 0}
    };

    return add_command(client, command_str, command_time);
}

// Dequeue a command from the command queue of the client
command_t *dequeue_command(command_queue_t *queue)
{
    command_t *command_node = NULL;

    if (queue == NULL || queue->front == NULL)
        return NULL;
    command_node = queue->front;
    queue->front = queue->front->next;
    if (queue->front == NULL)
        queue->back = NULL;
    queue->size--;
    return command_node;
}

// Free the command queue of the client
void free_command_queue(command_queue_t *queue)
{
    command_t *command_node = NULL;
    command_t *next = NULL;

    if (queue == NULL)
        return;
    command_node = queue->front;
    while (command_node != NULL) {
        next = command_node->next;
        free(command_node->command);
        free(command_node);
        command_node = next;
    }
    free(queue);
}

// Handle the client commands
void manage_queue(client_t *client, char *buffer)
{
    if (client->command_queue->size < 10)
        enqueue_command(client, buffer);
}
