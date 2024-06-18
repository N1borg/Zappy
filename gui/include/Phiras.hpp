/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** Phiras
*/

#pragma once

#include "IModel.hpp"

class Phiras : public IModel {
public:
    Phiras(Model model);
    ~Phiras() = default;

    void draw(Vector3 position, float scale, Color tint) const override;
    void SetRotationY(float yRotation);

private:
    Model _model;
    float _yRotation;
};
