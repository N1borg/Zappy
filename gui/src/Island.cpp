/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** Island
*/

#include "Island.hpp"

Island::Island(Model model) : AModel(model), _selected(false) {}

bool Island::isSelected() const
{
    return _selected;
}

void Island::setSelected(bool selected)
{
    _selected = selected;
}
