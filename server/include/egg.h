/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
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
