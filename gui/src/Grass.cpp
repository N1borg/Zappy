/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** Grass
*/

#include "Grass.hpp"

Grass::Grass(Model model) : _model(model) {}

void Grass::draw(Vector3 position, float scale, Color tint) const
{
    Vector3 rotationAxis = {0, 1, 0};
    Vector3 scaleVector = {scale, scale, scale};

    DrawModelEx(_model, position, rotationAxis, _yRotation * RAD2DEG, scaleVector, tint);
}

void Grass::SetRotationY(float yRotation)
{
    this->_yRotation = yRotation;
}
