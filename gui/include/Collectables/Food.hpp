/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** Food
*/

#pragma once

#include "AModel.hpp"

class Food : public AModel {
public:
    Food(Model model);
    ~Food() = default;

    void setIslandPosition(int islandPosition) override;
};
