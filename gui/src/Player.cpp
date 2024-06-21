/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** Player
*/

#include "Player.hpp"

Player::Player(Model model) : BaseModel(model) {}

void Player::setOrientation(Orientation orientation)
{
    this->_yRotation = static_cast<int>(orientation) * 90.0f;
}
