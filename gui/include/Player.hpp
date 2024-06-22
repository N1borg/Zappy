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
    Player(Model model, Team team);
    ~Player() = default;

    Team getTeam() const;
    void setOrientation(Orientation orientation);
private:
    Team _team;
    Orientation _orientation;
};
