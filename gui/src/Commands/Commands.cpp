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

void Commands::getPlayerPosition(const std::string& params)
{
    std::cout  << "Player Position: " << params << std::endl;
}

void Commands::getTileContent(const std::string& params)
{
    std::cout  << "Tile Content: " << params << std::endl;
}

void Commands::getTeamsName(const std::string& params)
{
    std::cout  << "Team Name: " << params << std::endl;
}

void Commands::getConnectionNewPlayer(const std::string& params)
{
    std::cout  << "New Player Connection: " << params << std::endl;
}

void Commands::getPlayerLevel(const std::string& params)
{
    std::cout  << "Player Level: " << params << std::endl;
}

void Commands::getPlayerInventory(const std::string& params)
{
    std::cout  << "Player Inventory: " << params << std::endl;
}

void Commands::getExpulsion(const std::string& params)
{
    std::cout  << "Player Expulsion: " << params << std::endl;
}
void Commands::getBroadcast(const std::string& params)
{
    std::cout  << "Broadcast: " << params << std::endl;
}

void Commands::getStartOfIncantation(const std::string& params)
{
    std::cout  << "Start of Incantation: " << params << std::endl;
}

void Commands::getEndOfIncantation(const std::string& params)
{
    std::cout  << "End of Incantation: " << params << std::endl;
}

void Commands::getLayingEggByPlayer(const std::string& params)
{
    std::cout  << "Laying Egg by Player: " << params << std::endl;
}

void Commands::getResourceDropping(const std::string& params)
{
    std::cout  << "Resource Dropping: " << params << std::endl;
}

void Commands::getResourceCollecting(const std::string& params)
{
    std::cout  << "Resource Collecting: " << params << std::endl;
}

void Commands::getPlayerDeath(const std::string& params)
{
    std::cout  << "Player Death: " << params << std::endl;
}

void Commands::getEggLaidByPlayer(const std::string& params)
{
    std::cout  << "Egg Laid by Player: " << params << std::endl;
}

void Commands::getPlayerConnectionInEgg(const std::string& params)
{
    std::cout  << "Player Connection in Egg: " << params << std::endl;
}

void Commands::getEggDeath(const std::string& params)
{
    std::cout  << "Death of Egg: " << params << std::endl;
}

void Commands::getTimeUnitRequest(const std::string& params)
{
    std::cout  << "Time Unit Request: " << params << std::endl;
}

void Commands::getTimeUnitModification(const std::string& params)
{
    std::cout  << "Time Unit Modification: " << params << std::endl;
}

void Commands::getEndOfGame(const std::string& params)
{
    std::cout  << "End of Game: " << params << std::endl;
}

void Commands::getServerMessage(const std::string& params)
{
    std::cout  << "Server Message: " << params << std::endl;
}

void Commands::getUnknownCommand(const std::string& params)
{
    std::cout  << "Unknown Command: " << params << std::endl;
}

void Commands::getCommandParameter(const std::string& params)
{
    std::cout  << "Command Parameter: " << params << std::endl;
}