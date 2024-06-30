/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** egg
*/

#pragma once

typedef struct egg_s {
    struct tile_s *tile;
    struct team_s *team;
    int id;
    struct egg_s *next_team;
    struct egg_s *next_tile;
} egg_t;
