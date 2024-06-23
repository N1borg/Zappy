/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** Player
*/

#pragma once

#include "AModel.hpp"
#include "Team.hpp"
#include "Orientation.hpp"

class Player : public AModel {
public:
    Player(Model model, int id, int x, int y, Orientation orientation, Team team);
    ~Player() = default;

    int getId() const;
    void setId(int id);
    int getX() const;
    void setX(int x);
    int getY() const;
    void setY(int y);
    Orientation getOrientation() const;
    void setOrientation(Orientation orientation);
    int getLevel() const;
    void setLevel(int level);
    Team getTeam() const;
private:
    int _id;
    int _x;
    int _y;
    Orientation _orientation;
    int _level;
    Team _team;
};
