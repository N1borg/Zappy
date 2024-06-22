/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** Island
*/

#pragma once

#include "AModel.hpp"

class Island : public AModel {
public:
    Island(Model model);
    ~Island() = default;

    bool isSelected() const;
    void setSelected(bool selected);
private:
    bool _selected;
};
