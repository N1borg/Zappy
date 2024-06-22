/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** Team
*/

#pragma once

#include <raylib.h>
#include <string>

class Team
{
public:
    Team(std::string name);
    ~Team() = default;

    std::string getTeamName() const;
    void setNumberPlayers(int numberPlayers);
    int getNumberPlayers() const;
    void setNumberEggs(int numberEggs);
    int getNumberEggs() const;
    void setNumberFreeSlots(int numberFreeSlots);
    int getNumberFreeSlots() const;
    void setTeamColor(Color color);
    Color getTeamColor() const;
private:
    std::string _name;
    Color _teamColor = WHITE;
    int _numberPlayers;
    int _numberEggs;
    int _numberFreeSlots;
};
