/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** Island
*/

#pragma once

#include "BaseModel.hpp"

class Island : public BaseModel {
public:
    Island(Model model);
    ~Island() = default;

    bool isSelected() const;
    void setSelected(bool selected);
private:
    bool _Selected;
};
