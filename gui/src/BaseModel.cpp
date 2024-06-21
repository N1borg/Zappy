/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** AModel
*/

#include "AModel.hpp"

AModel::AModel(Model model) : _model(model), _yRotation(0.0f) {}

void AModel::setRotationY(float yRotation)
{
    this->_yRotation = yRotation;
}

Model AModel::getModel() const
{
    return _model;
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
