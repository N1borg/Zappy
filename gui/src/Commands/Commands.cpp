/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Commands
*/

#include "Commands/Commands.hpp"

void Commands::getMapSize(const std::string &params)
{
    std::cout << "Map size: " << params << std::endl;
}

void Commands::getMapContent(const std::string& params)
{
    std::cout  << "Map content: " << params << std::endl;
}

void Commands::getPlayerPosition(const std::string& params)
{
    std::cout  << "Player Position: " << params << std::endl;
}