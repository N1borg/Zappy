/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Egg
*/

#pragma once

#include "Models/AModel.hpp"
#include "Team.hpp"

class Egg : public AModel {
public:
    Egg(Model _model, int id, int playerId, int x, int y, Team team);
    ~Egg() = default;

    int getId() const { return _id; }
    void setId(int id) { _id = id; }
    int getPlayerId() const { return _playerId; }
    void setPlayerId(int playerId) { _playerId = playerId; }
    int getX() const { return _x; }
    void setX(int x) { _x = x; }
    int getY() const { return _y; }
    void setY(int y) { _y = y; }
    Team getTeam() const { return _team; }
private:
    int _id;
    int _playerId;
    int _x;
    int _y;
    Team _team;
};
