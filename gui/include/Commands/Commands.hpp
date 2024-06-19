/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Commands
*/

#ifndef COMMANDS_HPP_
#define COMMANDS_HPP_

#include <iostream>

class Commands {
    public:
        Commands() = default;
        ~Commands() = default;

        void getMapSize(const std::string& params);
};

#endif /* !COMMANDS_HPP_ */