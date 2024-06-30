/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Player
*/

#pragma once

#include "Models/AModel.hpp"
#include "Team.hpp"

enum class Orientation {
    North = 0,
    East = 1,
    South = 2,
    West = 3
};

class Player : public AModel {
public:
    Player(Model model, int id, int x, int y, Orientation orientation, Team team) : AModel(model), _id(id), _x(x), _y(y),
        _level(1), _team(team) { _yRotation = static_cast<int>(orientation) * 90.0f; _islandPositionX = 0.0f; _islandPositionZ = 0.0f; }
    ~Player() = default;

    int getId() const { return _id; }
    void setId(int id) { _id = id; }
    int getX() const { return _x; }
    void setX(int x) { _x = x; }
    int getY() const { return _y; }
    void setY(int y) { _y = y; }
    float getOrientation() const { return _yRotation; }
    void setOrientation(Orientation orientation) { _yRotation = static_cast<int>(orientation) * 90.0f; }
    int getLevel() const { return _level; }
    void setLevel(int level) { _level = level; }
    Team getTeam() const { return _team; }
private:
    int _id;
    int _x;
    int _y;
    int _level;
    Team _team;
};
