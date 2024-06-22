/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** Map
*/

#pragma once

#include "Player.hpp"
#include "Collectables/Egg.hpp"
#include "Collectables/Food.hpp"
#include "Collectables/Linemate.hpp"
#include "Collectables/Deraumere.hpp"
#include "Collectables/Sibur.hpp"
#include "Collectables/Mendiane.hpp"
#include "Collectables/Phiras.hpp"
#include "Collectables/Thystame.hpp"
#include "Island.hpp"
#include "Grass.hpp"

#include <math.h>
#include <time.h>
#include <deque>
#include <vector>
#include <cfloat>

typedef struct Tile_s {
    std::deque<Player> players;
    std::deque<Egg> eggs;
    std::pair<Food, bool> food;
    std::pair<Linemate, bool> linemate;
    std::pair<Deraumere, bool> deraumere;
    std::pair<Sibur, bool> sibur;
    std::pair<Mendiane, bool> mendiane;
    std::pair<Phiras, bool> phiras;
    std::pair<Thystame, bool> thystame;
    std::pair<Island, bool> island;
    std::pair<Grass, bool> grass;

    Tile_s(Model _modelFood, Model _modelLinemate, Model _modelDeraumere,
        Model _modelSibur, Model _modelMendiane, Model _modelPhiras,
        Model _modelThystame, Model _modelIsland, Model _modelGrass)
            : food(std::make_pair(Food(_modelFood), false)),
            linemate(std::make_pair(Linemate(_modelLinemate), false)),
            deraumere(std::make_pair(Deraumere(_modelDeraumere), false)),
            sibur(std::make_pair(Sibur(_modelSibur), false)),
            mendiane(std::make_pair(Mendiane(_modelMendiane), false)),
            phiras(std::make_pair(Phiras(_modelPhiras), false)),
            thystame(std::make_pair(Thystame(_modelThystame), false)),
            island(std::make_pair(Island(_modelIsland), true)),
            grass(std::make_pair(Grass(_modelGrass), true)) {}
} Tile_t;

class Map {
public:
    Map(int width, int height);
    ~Map() = default;

    int getWidth() const;
    int getHeight() const;
    std::vector<std::vector<Tile_t>> getTiles() const;
    Tile_t getTile(int x, int y) const;
    void setPlayer(int x, int y, Player player);
    void setEgg(int x, int y, Egg egg);
    void destroyEgg(int x, int y, Egg egg);
    void setFood(int x, int y, bool value);
    void setLinemate(int x, int y, bool value);
    void setDeraumere(int x, int y, bool value);
    void setSibur(int x, int y, bool value);
    void setMendiane(int x, int y, bool value);
    void setPhiras(int x, int y, bool value);
    void setThystame(int x, int y, bool value);
    void setIsland(int x, int y, bool value);
    void setGrass(int x, int y, bool value);

    void draw();
    void drawTransparent();
    void selectTile(Ray ray);
    Tile_t getSelectedTile() const;

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
    Model _modelIsland;
    Model _modelGrass;

    std::vector<std::vector<Tile_t>> _tiles;
};
