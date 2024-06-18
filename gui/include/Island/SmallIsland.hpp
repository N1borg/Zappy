/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** SmallIsland
*/

#pragma once

#include "IModel.hpp"

class SmallIsland : public IModel {
    public:
        SmallIsland(Model model);
        ~SmallIsland() = default;

        void draw(Vector3 position, float scale, Color tint) const override;
        void setRotationY(float yRotation);

    private:
        Model _model;
        float _yRotation;
};
