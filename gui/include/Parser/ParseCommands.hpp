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

class ParseCommands : public IParser {
    public:
        ParseCommands();
        ~ParseCommands() = default;

        void parse(std::string msg);
    private:
        typedef void (Commands::*CommandFunc)(const std::string&);
        std::unordered_map<std::string, CommandFunc> _commandMap;
};
