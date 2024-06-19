/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** Grass
*/

#include "Grass.hpp"

Grass::Grass(Model model) : model(model) {}

void Grass::draw(Vector3 position, float scale, Color tint) const
{
    Vector3 rotationAxis = {0, 1, 0};
    Vector3 scaleVector = {scale, scale, scale};

    DrawModelEx(model, position, rotationAxis, yRotation * RAD2DEG, scaleVector, tint);
}

void Player::SetRotation(float yRotation)
{
    this->yRotation = yRotation;
}
