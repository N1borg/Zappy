/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** Team
*/

#pragma once

#include "RaylibWrapper.hpp"

#include <string>

class Team {
    public:
        Team(std::string name);
        ~Team() = default;

        void setNumberPlayers(int numberPlayers);
        void setNumberEggs(int numberEggs);
        void setTeamColor(Color color);

        std::string getTeamName() const;
        int getNumberPlayers() const;
        int getNumberEggs() const;
        Color getTeamColor() const;
    private:
        std::string _name;
        Color _teamColor = WHITE;
        int _numberPlayers;
        int _numberEggs;
};
