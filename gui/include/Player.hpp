/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** Player
*/

#pragma once

#include "BaseModel.hpp"
#include "Orientation.hpp"

class Player : public BaseModel {
public:
    Player(Model model);
    ~Player() = default;

    void setOrientation(Orientation orientation);
private:
    Orientation _orientation;
};
