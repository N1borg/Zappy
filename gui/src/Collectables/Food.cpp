/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** Food
*/

#include "Collectables/Food.hpp"

Food::Food(Model model) : AModel(model) {}

void Food::setIslandPosition(int islandPosition)
{
    float distance = 2.5f;

    switch (islandPosition) {
        case 0:
            _islandPositionX = 0.0f;
            _islandPositionZ = -distance;
            break;
        case 1:
            _islandPositionX = distance;
            _islandPositionZ = 0.0f;
            break;
        case 2:
            _islandPositionX = 0.0f;
            _islandPositionZ = distance;
            break;
        case 3:
            _islandPositionX = -distance;
            _islandPositionZ = 0.0f;
            break;
    }
}
