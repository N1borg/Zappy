/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Food
*/

#pragma once

#include "Models/AModel.hpp"

class Food : public AModel {
public:
    Food(Model model) : AModel(model) {}
    ~Food() = default;

    void setIslandPosition(int islandPosition) override;
};
