/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Linemate
*/

#pragma once

#include "Models/AModel.hpp"

class Linemate : public AModel {
public:
    Linemate(Model model) : AModel(model) {}
    ~Linemate() = default;
};
