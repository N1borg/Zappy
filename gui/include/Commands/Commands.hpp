/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Commands
*/

#pragma once

#include <iostream>

class Commands {
public:
    Commands() = default;
    ~Commands() = default;

    void getMapSize(const std::string& params);
    void getMapContent(const std::string& params);
    void getPlayerPosition(const std::string& params);
};
