/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** Deraumere
*/

#pragma once

#include "IModel.hpp"

class Deraumere : public IModel {
    public:
        Deraumere(Model model);
        ~Deraumere() = default;

        void draw(Vector3 position, float scale, Color tint) const override;
        void setRotation(float yRotation);

    private:
        Model model;
        float yRotation;
};
