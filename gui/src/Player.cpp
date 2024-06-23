/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** Player
*/

#include "Player.hpp"

Player::Player(Model model, int id, int x, int y, Orientation orientation, Team team) : AModel(model), _id(id), _x(x), _y(y), _orientation(orientation), _team(team)
{
    _yRotation = static_cast<int>(orientation) * 90.0f;
    _level = 1;
    _islandPositionX = 0.0f;
    _islandPositionZ = 0.0f;
}

int Player::getId() const
{
    return _id;
}

void Player::setId(int id)
{
    _id = id;
}

int Player::getX() const
{
    return _x;
}

void Player::setX(int x)
{
    _x = x;
}

int Player::getY() const
{
    return _y;
}

void Player::setY(int y)
{
    _y = y;
}

Orientation Player::getOrientation() const
{
    return _orientation;
}

void Player::setOrientation(Orientation orientation)
{
    _yRotation = static_cast<int>(orientation) * 90.0f;
}

int Player::getLevel() const
{
    return _level;
}

void Player::setLevel(int level)
{
    _level = level;
}

Team Player::getTeam() const
{
    return _team;
}
