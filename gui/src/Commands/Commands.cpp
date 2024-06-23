/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Commands
*/

#include "Commands/Commands.hpp"
#include "Game/Game.hpp"

void Commands::validateWelcome(const std::string &params, Game &game)
{
    std::cout << "Welcome to Zappy!" << params << std::endl;
    game.getSocket()->sendMessage("GRAPHIC\n");
    game.getSocket()->sendMessage("msz\n");
    game.getSocket()->sendMessage("tna\n");
    game.getSocket()->sendMessage("sgt\n");
    game.setWelcomeReceived(true);
}

void Commands::getMapSize(const std::string &params, Game &game)
{
    std::istringstream iss(params);
    int width, height;
    iss >> width >> height;

    game.getMap()->setWidth(width);
    game.getMap()->setHeight(height);
    game.getSocket()->sendMessage("bct\n");
    game.setMapSizeReceived(true);
}

void Commands::getPlayerPosition(const std::string &params, Game &game)
{
    std::istringstream iss(params);
    int playerNumber, x, y, orientation;
    iss >> playerNumber >> x >> y >> orientation;
    std::cout << "Player #" << playerNumber << " is at (" << x << ", " << y << ") facing orientation " << orientation << std::endl;
}

void Commands::getTileContent(const std::string &params, Game &game)
{
    std::istringstream iss(params);
    int x, y, q0, q1, q2, q3, q4, q5, q6;
    iss >> x >> y >> q0 >> q1 >> q2 >> q3 >> q4 >> q5 >> q6;
    std::cout << "Tile at (" << x << ", " << y << ") has resources: Food=" << q0 << ", Linemate=" << q1 << ", Deraumere=" << q2 << ", Sibur=" << q3 << ", Mendiane=" << q4 << ", Phiras=" << q5 << ", Thystame=" << q6 << std::endl;
    game.setTilesReceived(true);
}

void Commands::getTeamsName(const std::string &params, Game &game)
{
    std::istringstream iss(params);
    std::string teamName;
    while (iss >> teamName) {
        Team newTeam(teamName);

        Color colors[] = {RED, GREEN, BLUE, YELLOW, PURPLE, LIGHTGRAY, ORANGE, BEIGE, MAROON, LIME, DARKBLUE, GOLD, PINK, VIOLET, BROWN, DARKGRAY, DARKPURPLE};
        Color color = colors[rand() % 17];
        bool colorFound = false;

        // Check if color is already taken
        while (!colorFound) {
            colorFound = true;
            for (auto &team : game.getTeams()) {
                Color teamColor = team.getTeamColor();
                if ((teamColor.r == color.r) && (teamColor.g == color.g) && (teamColor.b == color.b)) {
                    color = colors[rand() % 17];
                    colorFound = false;
                    break;
                }
            }
        }

        newTeam.setTeamColor(color);
        game.addTeam(newTeam);
    }
    game.setPlayersReceived(true);
}

void Commands::getConnectionNewPlayer(const std::string &params, Game &game)
{
    std::istringstream iss(params);
    int playerNumber, x, y, orientation, level;
    std::string teamName;
    iss >> playerNumber >> x >> y >> orientation >> level >> teamName;
    std::cout << "New player #" << playerNumber << " from team " << teamName << " at (" << x << ", " << y << ") facing " << orientation << " at level " << level << std::endl;
}

void Commands::getPlayerLevel(const std::string &params, Game &game)
{
    std::istringstream iss(params);
    int playerNumber, level;
    iss >> playerNumber >> level;
    std::cout << "Player #" << playerNumber << " is at level " << level << std::endl;
}

void Commands::getPlayerInventory(const std::string &params, Game &game)
{
    std::istringstream iss(params);
    std::string teamName;
    while (iss >> teamName) {
        std::cout << "Team name: " << teamName << std::endl;
    }
}

void Commands::getExpulsion(const std::string &params, Game &game)
{
    std::istringstream iss(params);
    int playerNumber;
    iss >> playerNumber;
    std::cout << "Player #" << playerNumber << " has been expelled." << std::endl;
}

void Commands::getBroadcast(const std::string &params, Game &game)
{
    std::istringstream iss(params);
    int playerNumber;
    std::string message;
    iss >> playerNumber;
    std::getline(iss, message);
    std::cout << "Player #" << playerNumber << " broadcasts: " << message << std::endl;
}

void Commands::getStartOfIncantation(const std::string &params, Game &game)
{
    std::cout  << "Start of Incantation: " << params << std::endl;
}

void Commands::getEndOfIncantation(const std::string &params, Game &game)
{
    std::istringstream iss(params);
    int x, y, result;
    iss >> x >> y >> result;
    std::cout << "Incantation at (" << x << ", " << y << ") ended with result: " << (result ? "Success" : "Failure") << std::endl;
}

void Commands::getLayingEggByPlayer(const std::string &params, Game &game)
{
    std::istringstream iss(params);
    int playerNumber;
    iss >> playerNumber;
    std::cout << "Player #" << playerNumber << " has laid an egg." << std::endl;
}

void Commands::getResourceDropping(const std::string &params, Game &game)
{
    std::istringstream iss(params);
    int playerNumber, resourceIndex;
    iss >> playerNumber >> resourceIndex;
    std::cout << "Player #" << playerNumber << " dropped resource " << resourceIndex << std::endl;
}

void Commands::getResourceCollecting(const std::string &params, Game &game)
{
    std::istringstream iss(params);
    int playerNumber, resourceIndex;
    iss >> playerNumber >> resourceIndex;
    std::cout << "Player #" << playerNumber << " collected resource " << resourceIndex << std::endl;
}

void Commands::getPlayerDeath(const std::string &params, Game &game)
{
    std::istringstream iss(params);
    int playerNumber;
    iss >> playerNumber;
    std::cout << "Player #" << playerNumber << " has died." << std::endl;
}

void Commands::getEggLaidByPlayer(const std::string &params, Game &game)
{
     std::istringstream iss(params);
    int eggNumber, playerNumber, x, y;
    iss >> eggNumber >> playerNumber >> x >> y;
    std::cout << "Egg #" << eggNumber << " laid by Player #" << playerNumber << " at (" << x << ", " << y << ")." << std::endl;
}

void Commands::getPlayerConnectionInEgg(const std::string &params, Game &game)
{
    std::istringstream iss(params);
    int eggNumber;
    iss >> eggNumber;
    std::cout << "Player connected from Egg #" << eggNumber << "." << std::endl;
}

void Commands::getEggDeath(const std::string &params, Game &game)
{
    std::istringstream iss(params);
    int eggNumber;
    iss >> eggNumber;
    std::cout << "Egg #" << eggNumber << " has died." << std::endl;
}

void Commands::getTimeUnitRequest(const std::string &params, Game &game)
{
    int timeUnit;

    try {
        timeUnit = std::stoi(params);
        game.setTimeUnit(timeUnit);
    } catch (const std::exception &e) {
        RaylibWrapper::log(LOG_ERROR, "INIT: Invalid frequence");
    }
}

void Commands::getTimeUnitModification(const std::string &params, Game &game)
{
    std::istringstream iss(params);
    int newTimeUnit;
    iss >> newTimeUnit;
    game.setTimeUnit(newTimeUnit);
    game.setTimeUnitReceived(true);
}

void Commands::getEndOfGame(const std::string &params, Game &game)
{
    std::istringstream iss(params);
    std::string teamName;
    iss >> teamName;
    std::cout << "Game over! Winning team: " << teamName << std::endl;
}

void Commands::getServerMessage(const std::string &params, Game &game)
{
    std::cout  << "Server Message: " << params << std::endl;
}

void Commands::getUnknownCommand(const std::string &params, Game &game)
{
    RaylibWrapper::log(LOG_WARNING, "Unknown command");
}

void Commands::getCommandParameter(const std::string &params, Game &game)
{
    RaylibWrapper::log(LOG_WARNING, "Bad command parameters");
}
