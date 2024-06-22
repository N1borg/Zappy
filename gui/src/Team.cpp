/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** Team
*/

#include "Team.hpp"

Team::Team(std::string name)
{
    _name = name;
}

std::string Team::getTeamName() const
{
    return _name;
}

void Team::setTeamColor(Color color)
{
    _teamColor = color;
}

Color Team::getTeamColor() const
{
    return _teamColor;
}

void Team::setNumberPlayers(int numberPlayers)
{
    _numberPlayers = numberPlayers;
}

int Team::getNumberPlayers() const
{
    return _numberPlayers;
}

void Team::setNumberEggs(int numberEggs)
{
    _numberEggs = numberEggs;
}

int Team::getNumberEggs() const
{
    return _numberEggs;
}

void Team::setNumberFreeSlots(int numberFreeSlots)
{
    _numberFreeSlots = numberFreeSlots;
}

int Team::getNumberFreeSlots() const
{
    return _numberFreeSlots;
}
