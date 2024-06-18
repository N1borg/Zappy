/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** MediumIsland
*/

#include "Island/MediumIsland.hpp"

MediumIsland::MediumIsland(Model model) : model(model) {}

void MediumIsland::draw(Vector3 position, float scale, Color tint) const
{
    Vector3 rotationAxis = {0, 1, 0};
    Vector3 scaleVector = {scale, scale, scale};

    DrawModelEx(model, position, rotationAxis, yRotation * RAD2DEG, scaleVector, tint);
}

Model MediumIsland::getModel() const
{
    return model;
}
