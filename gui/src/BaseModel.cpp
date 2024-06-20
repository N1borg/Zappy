/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** BaseModel
*/

#include "BaseModel.hpp"

BaseModel::BaseModel(Model model) : _model(model), _yRotation(0.0f) {}

void BaseModel::draw(Vector3 position, float scale, Color tint) const
{
    Vector3 rotationAxis = {0, 1, 0};
    Vector3 scaleVector = {scale, scale, scale};

    DrawModelEx(_model, position, rotationAxis, _yRotation * RAD2DEG, scaleVector, tint);
}

void BaseModel::drawWires(Vector3 position, float scale, Color tint) const
{
    Vector3 rotationAxis = {0, 1, 0};
    Vector3 scaleVector = {scale, scale, scale};

    DrawModelWiresEx(_model, position, rotationAxis, _yRotation * RAD2DEG, scaleVector, tint);
}

void BaseModel::setRotationY(float yRotation)
{
    this->_yRotation = yRotation;
}
