/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** AModel
*/

#include "AModel.hpp"

AModel::AModel(Model model) : _model(model), _islandPositionX(0.0f), _islandPositionZ(0.0f), _yRotation(0.0f) {}

Model AModel::getModel() const
{
    return _model;
}

void AModel::setIslandPosition(int islandPosition = 0)
{
    float distance = 4.0f;
    float angle = islandPosition * (M_PI / 3);

    // Calculate X and Z positions using parametric equations of a circle
    _islandPositionX = distance * sin(angle);
    _islandPositionZ = distance * cos(angle);
}

int AModel::getIslandPositionX() const
{
    return _islandPositionX;
}

int AModel::getIslandPositionZ() const
{
    return _islandPositionZ;
}

void AModel::setRotationY(float yRotation)
{
    _yRotation = yRotation;
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
