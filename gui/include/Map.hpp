/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** Map
*/

#pragma once

#include "Camera.hpp"
#include "Player.hpp"
#include "Egg.hpp"
#include "Food.hpp"
#include "Linemate.hpp"
#include "Deraumere.hpp"
#include "Sibur.hpp"
#include "Mendiane.hpp"
#include "Phiras.hpp"
#include "Thystame.hpp"
#include "SmallIsland.hpp"
#include "MediumIsland.hpp"
#include "BigIsland.hpp"

#include <math.h>
#include <time.h>
#include <vector>

typedef struct Tile_s {
    std::pair<Player, bool> player;
    std::pair<Egg, bool> egg;
    std::pair<Food, bool> food;
    std::pair<Linemate, bool> linemate;
    std::pair<Deraumere, bool> deraumere;
    std::pair<Sibur, bool> sibur;
    std::pair<Mendiane, bool> mendiane;
    std::pair<Phiras, bool> phiras;
    std::pair<Thystame, bool> thystame;
    std::pair<SmallIsland, bool> smallIsland;
    std::pair<MediumIsland, bool> mediumIsland;
    std::pair<BigIsland, bool> bigIsland;

    Tile_s(Model modelPlayer, Model modelEgg, Model modelFood, Model modelLinemate,
    Model modelDeraumere, Model modelSibur, Model modelMendiane, Model modelPhiras,
    Model modelThystame, Model modelSmallIsland, Model modelMediumIsland, Model modelBigIsland)
        : player(std::make_pair(Player(modelPlayer), false)),
            egg(std::make_pair(Egg(modelEgg), false)),
            food(std::make_pair(Food(modelFood), false)),
            linemate(std::make_pair(Linemate(modelLinemate), false)),
            deraumere(std::make_pair(Deraumere(modelDeraumere), false)),
            sibur(std::make_pair(Sibur(modelSibur), false)),
            mendiane(std::make_pair(Mendiane(modelMendiane), false)),
            phiras(std::make_pair(Phiras(modelPhiras), false)),
            thystame(std::make_pair(Thystame(modelThystame), false)),
            smallIsland(std::make_pair(SmallIsland(modelSmallIsland), true)),
            mediumIsland(std::make_pair(MediumIsland(modelMediumIsland), false)),
            bigIsland(std::make_pair(BigIsland(modelBigIsland), false)) {}
} Tile_t;

class Map {
public:
    Map(int width, int height);
    ~Map() = default;

    std::vector<std::vector<Tile_t>> getTiles() const;
    void setPlayer(int x, int y, bool value);
    void setEgg(int x, int y, bool value);
    void setFood(int x, int y, bool value);
    void setLinemate(int x, int y, bool value);
    void setDeraumere(int x, int y, bool value);
    void setSibur(int x, int y, bool value);
    void setMendiane(int x, int y, bool value);
    void setPhiras(int x, int y, bool value);
    void setThystame(int x, int y, bool value);
    void setSmallIsland(int x, int y, bool value);
    void setMediumIsland(int x, int y, bool value);
    void setBigIsland(int x, int y, bool value);

    void draw();

    void unload();

private:
    int _width;
    int _height;
    Model _modelPlayer;
    Model _modelEgg;
    Model _modelFood;
    Model _modelLinemate;
    Model _modelDeraumere;
    Model _modelSibur;
    Model _modelMendiane;
    Model _modelPhiras;
    Model _modelThystame;
    Model _modelSmallIsland;
    Model _modelMediumIsland;
    Model _modelBigIsland;

    std::vector<std::vector<Tile_t>> _tiles;
};
