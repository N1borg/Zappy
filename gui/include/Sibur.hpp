/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** Sibur
*/

#pragma once

#include "IModel.hpp"

class Sibur : public IModel {
public:
    Sibur(Model model);
    ~Sibur() = default;

    void draw(Vector3 position, float scale, Color tint) const override;
    void SetRotation(float yRotation);

private:
    Model model;
    float yRotation;
};