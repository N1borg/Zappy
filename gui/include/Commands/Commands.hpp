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

class Commands {
    public:
        Commands() = default;
        ~Commands() = default;

        void getMapSize(const std::string& params);
        void getPlayerPosition(const std::string& params);
        void getTileContent(const std::string& params);
        void getTeamsName(const std::string& params);
        void getConnectionNewPlayer(const std::string& params);
        void getPlayerLevel(const std::string& params);
        void getPlayerInventory(const std::string& params);
        void getExpulsion(const std::string& params);
        void getStartOfIncantation(const std::string& params);
        void getEndOfIncantation(const std::string& params);
        void getLayingEggByPlayer(const std::string& params);
        void getResourceDropping(const std::string& params);
        void getResourceCollecting(const std::string& params);
        void getPlayerDeath(const std::string& params);
        void getEggLaidByPlayer(const std::string& params);
        void getPlayerConnectionInEgg(const std::string& params);
        void getEggDeath(const std::string& params);
        void getTimeUnitRequest(const std::string& params);
        void getTimeUnitModification(const std::string& params);
        void getEndOfGame(const std::string& params);
        void getServerMessage(const std::string& params);
        void getUnknownCommand(const std::string& params);
        void getCommandParameter(const std::string& params);
        void getBroadcast(const std::string& params);
};
