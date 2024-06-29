/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** Egg
*/

#pragma once

#include "AModel.hpp"
#include "Team.hpp"

class Egg : public AModel {
public:
    Egg(Model _model, int id, int playerId, int x, int y, Team team);
    ~Egg() = default;

    int getId() const;
    void setId(int id);
    int getPlayerId() const;
    void setPlayerId(int playerId);
    int getX() const;
    void setX(int x);
    int getY() const;
    void setY(int y);
    Team getTeam() const;
private:
    int _id;
    int _playerId;
    int _x;
    int _y;
    Team _team;
};