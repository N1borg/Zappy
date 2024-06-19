/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** Thystame
*/

#pragma once

#include "IModel.hpp"

class Thystame : public IModel {
    public:
        Thystame(Model model);
        ~Thystame() = default;

        void draw(Vector3 position, float scale, Color tint) const override;
        void setRotationY(float yRotation);

    private:
        Model _model;
        float _yRotation;
};
