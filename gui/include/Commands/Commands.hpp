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
#include <memory>

class Map;

class Commands {
    public:
        Commands() = default;
        ~Commands() = default;

        void getMapSize(const std::string &params, std::shared_ptr<Map> &map);
        void getPlayerPosition(const std::string &params, std::shared_ptr<Map> &map);
        void getTileContent(const std::string &params, std::shared_ptr<Map> &map);
        void getTeamsName(const std::string &params, std::shared_ptr<Map> &map);
        void getConnectionNewPlayer(const std::string &params, std::shared_ptr<Map> &map);
        void getPlayerLevel(const std::string &params, std::shared_ptr<Map> &map);
        void getPlayerInventory(const std::string &params, std::shared_ptr<Map> &map);
        void getExpulsion(const std::string &params, std::shared_ptr<Map> &map);
        void getStartOfIncantation(const std::string &params, std::shared_ptr<Map> &map);
        void getEndOfIncantation(const std::string &params, std::shared_ptr<Map> &map);
        void getLayingEggByPlayer(const std::string &params, std::shared_ptr<Map> &map);
        void getResourceDropping(const std::string &params, std::shared_ptr<Map> &map);
        void getResourceCollecting(const std::string &params, std::shared_ptr<Map> &map);
        void getPlayerDeath(const std::string &params, std::shared_ptr<Map> &map);
        void getEggLaidByPlayer(const std::string &params, std::shared_ptr<Map> &map);
        void getPlayerConnectionInEgg(const std::string &params, std::shared_ptr<Map> &map);
        void getEggDeath(const std::string &params, std::shared_ptr<Map> &map);
        void getTimeUnitRequest(const std::string &params, std::shared_ptr<Map> &map);
        void getTimeUnitModification(const std::string &params, std::shared_ptr<Map> &map);
        void getEndOfGame(const std::string &params, std::shared_ptr<Map> &map);
        void getServerMessage(const std::string &params, std::shared_ptr<Map> &map);
        void getUnknownCommand(const std::string &params, std::shared_ptr<Map> &map);
        void getCommandParameter(const std::string &params, std::shared_ptr<Map> &map);
        void getBroadcast(const std::string &params, std::shared_ptr<Map> &map);
};
