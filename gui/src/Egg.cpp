/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** Egg
*/

#include "Egg.hpp"

Egg::Egg(Model model) : model(model) {}

void Egg::draw(Vector3 position, float scale, Color tint) const
{
    Vector3 rotationAxis = {0, 1, 0};
    Vector3 scaleVector = {scale, scale, scale};

    DrawModelEx(model, position, rotationAxis, yRotation * RAD2DEG, scaleVector, tint);
}
