/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ParseCommands
*/

#pragma once

#include "IParser.hpp"
#include "Commands/Commands.hpp"

#include <functional>
#include <unordered_map>
#include <string>

class Game;

class ParseCommands : public IParser {
    public:
        ParseCommands();
        ~ParseCommands() = default;

        void parse(const std::string &msg, Game &game);
    private:
        typedef void (Commands::*CommandFunc)(const std::string&, Game&);
        std::unordered_map<std::string, CommandFunc> _commandMap;
};
