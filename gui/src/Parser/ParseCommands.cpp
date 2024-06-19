/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ParseCommands
*/

#include "Parser/ParseCommands.hpp"

ParseCommands::ParseCommands()
{
    _commandMap["msz"] = &Commands::getMapSize;
}

void ParseCommands::parse(std::string msg)
{
    std::string command, params;
    size_t pos = msg.find(' ');
    if (pos != std::string::npos) {
        command = msg.substr(0, pos);
        params = msg.substr(pos + 1);
    } else
        command = msg;

    auto it = _commandMap.find(command);
    if (it != _commandMap.end())
        std::invoke(it->second, Commands(), params);
    else
        std::cerr << "Commande inconnue: " << command << std::endl;
}
