/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ParseCommands
*/

#ifndef PARSECOMMANDS_HPP_
#define PARSECOMMANDS_HPP_

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

#endif /* !PARSECOMMANDS_HPP_ */
