/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Commands
*/

#include "Commands/Commands.hpp"
#include "Map.hpp"

void Commands::getMapSize(const std::string &params, std::shared_ptr<Map> &map)
{
    std::istringstream iss(params);
    int width, height;
    iss >> width >> height;
    std::cout << map->getWidth() << std::endl;
    std::cout << "Map size: Width = " << width << ", Height = " << height << std::endl;
}

void Commands::getPlayerPosition(const std::string &params, std::shared_ptr<Map> &map)
{
    std::istringstream iss(params);
    int playerNumber, x, y, orientation;
    iss >> playerNumber >> x >> y >> orientation;
    map->delPlayer(playerNumber);
    map->addPlayer(playerNumber, x, y, Orientation (orientation + 1), 1, map->getTeamByPlayerId(playerNumber).getTeamName());
    std::cout << "Player #" << playerNumber << " is at (" << x << ", " << y << ") facing orientation " << orientation << std::endl;
}

void Commands::getTileContent(const std::string &params, std::shared_ptr<Map> &map)
{
    std::istringstream iss(params);
    int x, y, q0, q1, q2, q3, q4, q5, q6;
    iss >> x >> y >> q0 >> q1 >> q2 >> q3 >> q4 >> q5 >> q6;
    std::cout << "Tile at (" << x << ", " << y << ") has resources: Food=" << q0 << ", Linemate=" << q1 << ", Deraumere=" << q2 << ", Sibur=" << q3 << ", Mendiane=" << q4 << ", Phiras=" << q5 << ", Thystame=" << q6 << std::endl;
}

void Commands::getTeamsName(const std::string &params, std::shared_ptr<Map> &map)
{
    std::istringstream iss(params);
    std::string teamName;
    while (iss >> teamName) {
        std::cout << "Team name: " << teamName << std::endl;
    }
}

void Commands::getConnectionNewPlayer(const std::string &params, std::shared_ptr<Map> &map)
{
    std::istringstream iss(params);
    int playerNumber, x, y, orientation, level;
    std::string teamName;
    iss >> playerNumber >> x >> y >> orientation >> level >> teamName;
    map->addPlayer(playerNumber, x, y, Orientation (orientation + 1), level, teamName);
    std::cout << "New player #" << playerNumber << " from team " << teamName << " at (" << x << ", " << y << ") facing " << orientation << " at level " << level << std::endl;
}

void Commands::getPlayerLevel(const std::string &params, std::shared_ptr<Map> &map)
{
    std::istringstream iss(params);
    int playerNumber, level;
    iss >> playerNumber >> level;
    map->getPlayerById(playerNumber).setLevel(level);
    std::cout << "Player #" << playerNumber << " is at level " << level << std::endl;
}

void Commands::getPlayerInventory(const std::string &params, std::shared_ptr<Map> &map)
{
    std::istringstream iss(params);
    std::string teamName;
    while (iss >> teamName) {
        std::cout << "Team name: " << teamName << std::endl;
    }
}

void Commands::getExpulsion(const std::string &params, std::shared_ptr<Map> &map)
{
    std::istringstream iss(params);
    int playerNumber;
    iss >> playerNumber;
    std::cout << "Player #" << playerNumber << " has been expelled." << std::endl;
}

void Commands::getBroadcast(const std::string &params, std::shared_ptr<Map> &map)
{
    std::istringstream iss(params);
    int playerNumber;
    std::string message;
    iss >> playerNumber;
    std::getline(iss, message);
    std::cout << "Player #" << playerNumber << " broadcasts: " << message << std::endl;
}

void Commands::getStartOfIncantation(const std::string &params, std::shared_ptr<Map> &map)
{
    std::cout  << "Start of Incantation: " << params << std::endl;
}

void Commands::getEndOfIncantation(const std::string &params, std::shared_ptr<Map> &map)
{
    std::istringstream iss(params);
    int x, y, result;
    iss >> x >> y >> result;
    std::cout << "Incantation at (" << x << ", " << y << ") ended with result: " << (result ? "Success" : "Failure") << std::endl;
}

void Commands::getLayingEggByPlayer(const std::string &params, std::shared_ptr<Map> &map)
{
    std::istringstream iss(params);
    int playerNumber;
    iss >> playerNumber;
    std::cout << "Player #" << playerNumber << " has laid an egg." << std::endl;
}

void Commands::getResourceDropping(const std::string &params, std::shared_ptr<Map> &map)
{
    std::istringstream iss(params);
    int playerNumber, resourceIndex;
    iss >> playerNumber >> resourceIndex;
    switch (resourceIndex) {
        case 0:
            map->addFood(map->getPlayerById(playerNumber).getX(), map->getPlayerById(playerNumber).getY());
            break;
        case 1:
            map->addLinemate(map->getPlayerById(playerNumber).getX(), map->getPlayerById(playerNumber).getY());
            break;
        case 2:
            map->addDeraumere(map->getPlayerById(playerNumber).getX(), map->getPlayerById(playerNumber).getY());
            break;
        case 3:
            map->addSibur(map->getPlayerById(playerNumber).getX(), map->getPlayerById(playerNumber).getY());
            break;
        case 4:
            map->addMendiane(map->getPlayerById(playerNumber).getX(), map->getPlayerById(playerNumber).getY());
            break;
        case 5:
            map->addPhiras(map->getPlayerById(playerNumber).getX(), map->getPlayerById(playerNumber).getY());
            break;
        case 6:
            map->addThystame(map->getPlayerById(playerNumber).getX(), map->getPlayerById(playerNumber).getY());
            break;
    }
    std::cout << "Player #" << playerNumber << " dropped resource " << resourceIndex << std::endl;
}

void Commands::getResourceCollecting(const std::string &params, std::shared_ptr<Map> &map)
{
    std::istringstream iss(params);
    int playerNumber, resourceIndex;
    iss >> playerNumber >> resourceIndex;
    switch (resourceIndex) {
        case 0:
            map->delFood(map->getPlayerById(playerNumber).getX(), map->getPlayerById(playerNumber).getY());
            break;
        case 1:
            map->delLinemate(map->getPlayerById(playerNumber).getX(), map->getPlayerById(playerNumber).getY());
            break;
        case 2:
            map->delDeraumere(map->getPlayerById(playerNumber).getX(), map->getPlayerById(playerNumber).getY());
            break;
        case 3:
            map->delSibur(map->getPlayerById(playerNumber).getX(), map->getPlayerById(playerNumber).getY());
            break;
        case 4:
            map->delMendiane(map->getPlayerById(playerNumber).getX(), map->getPlayerById(playerNumber).getY());
            break;
        case 5:
            map->delPhiras(map->getPlayerById(playerNumber).getX(), map->getPlayerById(playerNumber).getY());
            break;
        case 6:
            map->delThystame(map->getPlayerById(playerNumber).getX(), map->getPlayerById(playerNumber).getY());
            break;
    }
    std::cout << "Player #" << playerNumber << " collected resource " << resourceIndex << std::endl;
}

void Commands::getPlayerDeath(const std::string &params, std::shared_ptr<Map> &map)
{
    std::istringstream iss(params);
    int playerNumber;
    iss >> playerNumber;
    map->delPlayer(playerNumber);
    std::cout << "Player #" << playerNumber << " has died." << std::endl;
}

void Commands::getEggLaidByPlayer(const std::string &params, std::shared_ptr<Map> &map)
{
     std::istringstream iss(params);
    int eggNumber, playerNumber, x, y;
    iss >> eggNumber >> playerNumber >> x >> y;
    map->addEgg(eggNumber, playerNumber, x, y, map->getTeamByPlayerId(playerNumber).getTeamName());
    std::cout << "Egg #" << eggNumber << " laid by Player #" << playerNumber << " at (" << x << ", " << y << ")." << std::endl;
}

void Commands::getPlayerConnectionInEgg(const std::string &params, std::shared_ptr<Map> &map)
{
    std::istringstream iss(params);
    int eggNumber;
    iss >> eggNumber;
    map->delEgg(eggNumber);
    std::cout << "Player connected from Egg #" << eggNumber << "." << std::endl;
}

void Commands::getEggDeath(const std::string &params, std::shared_ptr<Map> &map)
{
    std::istringstream iss(params);
    int eggNumber;
    iss >> eggNumber;
    map->delEgg(eggNumber);
    std::cout << "Egg #" << eggNumber << " has died." << std::endl;
}

void Commands::getTimeUnitRequest(const std::string &params, std::shared_ptr<Map> &map)
{
    std::istringstream iss(params);
    int timeUnit;
    iss >> timeUnit;
    map->setFrequency(timeUnit);
}

void Commands::getTimeUnitModification(const std::string &params, std::shared_ptr<Map> &map)
{
    std::istringstream iss(params);
    int newTimeUnit;
    iss >> newTimeUnit;
    map->setFrequency(newTimeUnit);
}

void Commands::getEndOfGame(const std::string &params, std::shared_ptr<Map> &map)
{
    std::istringstream iss(params);
    std::string teamName;
    iss >> teamName;
    std::cout << "Game over! Winning team: " << teamName << std::endl;
}

void Commands::getServerMessage(const std::string &params, std::shared_ptr<Map> &map)
{
    std::cout  << "Server Message: " << params << std::endl;
}

void Commands::getUnknownCommand(const std::string &params, std::shared_ptr<Map> &map)
{
    std::cout  << "Unknown Command: " << params << std::endl;
}

void Commands::getCommandParameter(const std::string &params, std::shared_ptr<Map> &map)
{
    std::cout  << "Command Parameter: " << params << std::endl;
}
