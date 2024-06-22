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
    Egg(Model _model, Team team);
    ~Egg() = default;

    Team getTeam() const;
private:
    Team _team;
};
