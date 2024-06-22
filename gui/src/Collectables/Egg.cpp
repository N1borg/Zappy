/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** Egg
*/

#include "Collectables/Egg.hpp"

Egg::Egg(Model model, int id, int playerId, int x, int y, Team team)
    : AModel(model), _id{id}, _playerId{playerId}, _x{x}, _y{y}, _team{team}
{
    _yRotation = 0.0f;
    _islandPositionX = 0.0f;
    _islandPositionZ = 0.0f;
}

int Egg::getId() const
{
    return _id;
}

int Egg::setId(int id)
{
    _id = id;
}

int Egg::getPlayerId() const
{
    return _playerId;
}

int Egg::setPlayerId() const
{
    return _playerId;
}

int Egg::getX() const
{
    return _x;
}

int Egg::setX(int x)
{
    _x = x;
}

int Egg::getY() const
{
    return _y;
}

int Egg::setY(int y)
{
    _y = y;
}

Team Egg::getTeam() const
{
    return _team;
}
