/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** BigIsland
*/

#pragma once

#include "IModel.hpp"

class BigIsland : public IModel {
public:
    BigIsland(Model model);
    ~BigIsland() = default;

    void draw(Vector3 position, float scale, Color tint) const override;
    void SetRotationY(float yRotation);

private:
    Model _model;
    float _yRotation;
};
