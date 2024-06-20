/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Commands
*/

#ifndef COMMANDS_HPP_
#define COMMANDS_HPP_

#include <iostream>

class Commands {
    public:
        Commands() = default;
        ~Commands() = default;

        void getMapSize(const std::string& params);
        void getMapContent(const std::string& params);
        void getPlayerPosition(const std::string& params);
        void getTileContent(const std::string& params);
        void getTeamName(const std::string& params);
        void getConnectionNewPlayer(const std::string& params);
        void getPlayerLevel(const std::string& params);
        void getPlayerInventory(const std::string& params);
        void getPlayerExpulsion(const std::string& params);
        void getStartofIncantation(const std::string& params);
        void getEndofIncantation(const std::string& params);
        void getLayingEggbyPlayer(const std::string& params);
        void getResourceDropping(const std::string& params);
        void getResourceCollecting(const std::string& params);
        void getPlayerDeath(const std::string& params);
        void getLaidEggbyPlayer(const std::string& params);
        void getPlayerConnectioninEgg(const std::string& params);
        void getEggDeath(const std::string& params);
        void getTimeUnitRequest(const std::string& params);
        void getTimeUnitModification(const std::string& params);
        void getEndofGame(const std::string& params);
        void getServerMessage(const std::string& params);
        void getUnknownCommand(const std::string& params);
        void getCommandParameter(const std::string& params);
        void getBroadcast(const std::string& params);
};

#endif /* !COMMANDS_HPP_ */