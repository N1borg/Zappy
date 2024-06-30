/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** AModel
*/

#include "Models/AModel.hpp"

void AModel::setIslandPosition(int islandPosition = 0)
{
    float distance = 4.0f;
    float angle = islandPosition * (M_PI / 3);

    // Calculate X and Z positions using parametric equations of a circle
    _islandPositionX = distance * sin(angle);
    _islandPositionZ = distance * cos(angle);
}

void AModel::draw(Vector3 position, float scale, Color tint) const
{
    Vector3 rotationAxis = {0, 1, 0};
    Vector3 scaleVector = {scale, scale, scale};

    DrawModelEx(_model, position, rotationAxis, _yRotation * RAD2DEG, scaleVector, tint);
}

void AModel::drawWires(Vector3 position, float scale, Color tint) const
{
    Vector3 rotationAxis = {0, 1, 0};
    Vector3 scaleVector = {scale, scale, scale};

    DrawModelWiresEx(_model, position, rotationAxis, _yRotation * RAD2DEG, scaleVector, tint);
}
