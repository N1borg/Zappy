/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ParseCommands
*/

#pragma once

#include <functional>
#include <unordered_map>
#include <iostream>
#include <string>

#include "Commands/Commands.hpp"

class ParseCommands {
    public:
        ParseCommands();
        ~ParseCommands() = default;

        void parse(std::string msg);
    private:
        typedef void (Commands::*CommandFunc)(const std::string&);
        std::unordered_map<std::string, CommandFunc> _commandMap;
};
