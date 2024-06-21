/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** Island
*/

#include "Island.hpp"

Island::Island(Model model) : BaseModel(model), _Selected(false) {}

bool Island::isSelected() const
{
    return _Selected;
}

void Island::setSelected(bool selected)
{
    _Selected = selected;
}
