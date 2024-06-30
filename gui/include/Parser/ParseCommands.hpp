/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ParseCommands
*/

#pragma once

#include "IParser.hpp"
#include "Commands/Commands.hpp"
#include "Map.hpp"

#include <functional>
#include <unordered_map>
#include <string>
#include <memory>

class ParseCommands : public IParser {
public:
    ParseCommands();
    ~ParseCommands() = default;

    void parse(std::string msg, std::shared_ptr<Map> &map);
private:
    typedef void (Commands::*CommandFunc)(const std::string&, std::shared_ptr<Map>&);
    std::unordered_map<std::string, CommandFunc> _commandMap;
};
