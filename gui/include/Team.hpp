/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Team
*/

#pragma once

#include <raylib.h>
#include <string>

class Team {
public:
    Team(std::string name) : _name(name), _teamColor(WHITE), _numberPlayers(0), _numberEggs(0) {}
    ~Team() = default;

    std::string getTeamName() const { return _name; }
    void setNumberPlayers(int numberPlayers) { _numberPlayers = numberPlayers; }
    int getNumberPlayers() const { return _numberPlayers; }
    void setNumberEggs(int numberEggs) { _numberEggs = numberEggs; }
    int getNumberEggs() const { return _numberEggs; }
    void setTeamColor(Color color) { _teamColor = color; }
    Color getTeamColor() const { return _teamColor; }
private:
    std::string _name;
    Color _teamColor = WHITE;
    int _numberPlayers;
    int _numberEggs;
};
