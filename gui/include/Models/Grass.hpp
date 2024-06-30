/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Grass
*/

#pragma once

#include "Models/AModel.hpp"

class Grass : public AModel {
public:
    Grass(Model model) : AModel(model) {}
    ~Grass() = default;
};
