/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** Linemate
*/

#pragma once

#include "IModel.hpp"

class Linemate : public IModel {
public:
    Linemate(Model model);
    ~Linemate() = default;

    void draw(Vector3 position, float scale, Color tint) const override;
    void SetRotation(float yRotation);

private:
    Model model;
    float yRotation;
};
