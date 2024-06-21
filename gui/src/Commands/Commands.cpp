/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Commands
*/

#include "Commands/Commands.hpp"

void Commands::getMapSize(const std::string &params)
{
    std::istringstream iss(params);
    int width, height;
    iss >> width >> height;
    std::cout << "Map size: Width = " << width << ", Height = " << height << std::endl;
}

void Commands::getMapContent(const std::string& params)
{
    std::cout  << "Map content: " << params << std::endl;
}

void Commands::getPlayerPosition(const std::string& params)
{
    std::istringstream iss(params);
    int playerNumber, x, y, orientation;
    iss >> playerNumber >> x >> y >> orientation;
    std::cout << "Player #" << playerNumber << " is at (" << x << ", " << y << ") facing orientation " << orientation << std::endl;}

void Commands::getTileContent(const std::string& params)
{
    std::istringstream iss(params);
    int x, y, q0, q1, q2, q3, q4, q5, q6;
    iss >> x >> y >> q0 >> q1 >> q2 >> q3 >> q4 >> q5 >> q6;
    std::cout << "Tile at (" << x << ", " << y << ") has resources: Food=" << q0 << ", Linemate=" << q1 << ", Deraumere=" << q2 << ", Sibur=" << q3 << ", Mendiane=" << q4 << ", Phiras=" << q5 << ", Thystame=" << q6 << std::endl;
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
    std::istringstream iss(params);
    int playerNumber, level;
    iss >> playerNumber >> level;
    std::cout << "Player #" << playerNumber << " is at level " << level << std::endl;}

void Commands::getPlayerInventory(const std::string& params)
{
    std::istringstream iss(params);
    std::string teamName;
    while (iss >> teamName) {
        std::cout << "Team name: " << teamName << std::endl;
    }}

void Commands::getExpulsion(const std::string& params)
{
    std::istringstream iss(params);
    int playerNumber;
    iss >> playerNumber;
    std::cout << "Player #" << playerNumber << " has been expelled." << std::endl;
}

void Commands::getBroadcast(const std::string& params)
{
    std::istringstream iss(params);
    int playerNumber;
    std::string message;
    iss >> playerNumber;
    std::getline(iss, message);
    std::cout << "Player #" << playerNumber << " broadcasts: " << message << std::endl;
}

void Commands::getStartOfIncantation(const std::string& params)
{
    std::cout  << "Start of Incantation: " << params << std::endl;
}

void Commands::getEndOfIncantation(const std::string& params)
{
    std::istringstream iss(params);
    int x, y, result;
    iss >> x >> y >> result;
    std::cout << "Incantation at (" << x << ", " << y << ") ended with result: " << (result ? "Success" : "Failure") << std::endl;
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