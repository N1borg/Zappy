/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** Sibur
*/

#include "Collectables/Sibur.hpp"

Sibur::Sibur(Model model) : model(model) {}

void Sibur::draw(Vector3 position, float scale, Color tint) const
{
    Vector3 rotationAxis = {0, 1, 0};
    Vector3 scaleVector = {scale, scale, scale};

    DrawModelEx(model, position, rotationAxis, yRotation * RAD2DEG, scaleVector, tint);
}

void Sibur::setRotation(float yRotation)
{
    this->yRotation = yRotation;
}
