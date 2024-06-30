/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Island
*/

#pragma once

#include "Models/AModel.hpp"

class Island : public AModel {
public:
    Island(Model model) : AModel(model), _selected(false) {}
    ~Island() = default;

    bool isSelected() const { return _selected; }
    void setSelected(bool selected) { _selected = selected; }
private:
    bool _selected;
};
