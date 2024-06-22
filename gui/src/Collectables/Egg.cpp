/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** Egg
*/

#include "Collectables/Egg.hpp"

Egg::Egg(Model model, Team team) : AModel(model), _team(team)
{
    _yRotation = 0.0f;
    _islandPositionX = 0.0f;
    _islandPositionZ = 0.0f;
}

Team Egg::getTeam() const
{
    return _team;
}
