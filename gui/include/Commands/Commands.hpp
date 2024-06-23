/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Commands
*/

#pragma once

#include <iostream>
#include <sstream>
#include <string>

class Game;

class Commands {
    public:
        Commands() = default;
        ~Commands() = default;

        void validateWelcome(const std::string& params, Game &game);
        void getMapSize(const std::string& params, Game &game);
        void getPlayerPosition(const std::string& para, Game &game);
        void getTileContent(const std::string& params, Game &game);
        void getTeamsName(const std::string& param, Game &game);
        void getConnectionNewPlayer(const std::string& params, Game &game);
        void getPlayerLevel(const std::string& params, Game &game);
        void getPlayerInventory(const std::string& params, Game &game);
        void getExpulsion(const std::string& param, Game &game);
        void getStartOfIncantation(const std::string& para, Game &game);
        void getEndOfIncantation(const std::string& params, Game &game);
        void getLayingEggByPlayer(const std::string& param, Game &game);
        void getResourceDropping(const std::string& params, Game &game);
        void getResourceCollecting(const std::string& para, Game &game);
        void getPlayerDeath(const std::string& params, Game &game);
        void getEggLaidByPlayer(const std::string& params, Game &game);
        void getPlayerConnectionInEgg(const std::string& param, Game &game);
        void getEggDeath(const std::string& params, Game &game);
        void getTimeUnitRequest(const std::string& params, Game &game);
        void getTimeUnitModification(const std::string& params, Game &game);
        void getEndOfGame(const std::string& param, Game &game);
        void getServerMessage(const std::string& param, Game &game);
        void getUnknownCommand(const std::string& para, Game &game);
        void getCommandParameter(const std::string& params, Game &game);
        void getBroadcast(const std::string& param, Game &game);
};
