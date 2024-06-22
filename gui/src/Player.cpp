/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** Player
*/

#include "Player.hpp"

Player::Player(Model model, Team team) : AModel(model), _team(team)
{
    _islandPositionX = 0.0f;
    _islandPositionZ = 0.0f;
}

Team Player::getTeam() const
{
    return _team;
}

void Player::setOrientation(Orientation orientation)
{
    _yRotation = static_cast<int>(orientation) * 90.0f;
}
