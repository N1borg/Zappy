/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** Egg
*/

#pragma once

#include "IModel.hpp"

class Egg : public IModel {
public:
    Egg(Model model);
    ~Egg() = default;

    void draw(Vector3 position, float scale, Color tint) const override;

private:
    Model model;
    float yRotation;
};
