/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Egg
*/

#include "Models/Collectables/Egg.hpp"

Egg::Egg(Model model, int id, int playerId, int x, int y, Team team)
    : AModel(model), _id{id}, _playerId{playerId}, _x{x}, _y{y}, _team{team}
{
    _yRotation = 0.0f;
    _islandPositionX = 0.0f;
    _islandPositionZ = 0.0f;
    team.setNumberEggs(team.getNumberEggs() + 1);
}
