/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** MediumIsland
*/

#pragma once

#include "IModel.hpp"

class MediumIsland : public IModel {
    public:
        MediumIsland(Model model);
        ~MediumIsland() = default;

        void draw(Vector3 position, float scale, Color tint) const override;
        Model getModel() const;

    private:
        Model model;
        float yRotation;
};
