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
    std::pair<Food, int> food;
    std::pair<Linemate, int> linemate;
    std::pair<Deraumere, int> deraumere;
    std::pair<Sibur, int> sibur;
    std::pair<Mendiane, int> mendiane;
    std::pair<Phiras, int> phiras;
    std::pair<Thystame, int> thystame;
    std::pair<Island, int> island;
    std::pair<Grass, int> grass;

    Tile_s(Model _modelFood, Model _modelLinemate, Model _modelDeraumere,
        Model _modelSibur, Model _modelMendiane, Model _modelPhiras,
        Model _modelThystame, Model _modelIsland, Model _modelGrass)
            : food(std::make_pair(Food(_modelFood), 0)),
            linemate(std::make_pair(Linemate(_modelLinemate), 0)),
            deraumere(std::make_pair(Deraumere(_modelDeraumere), 0)),
            sibur(std::make_pair(Sibur(_modelSibur), 0)),
            mendiane(std::make_pair(Mendiane(_modelMendiane), 0)),
            phiras(std::make_pair(Phiras(_modelPhiras), 0)),
            thystame(std::make_pair(Thystame(_modelThystame), 0)),
            island(std::make_pair(Island(_modelIsland), 1)),
            grass(std::make_pair(Grass(_modelGrass), 1)) {}
} Tile_t;

class Map {
public:
    Map(int width, int height, int frequency);
    ~Map() = default;

    int getWidth() const;
    int getHeight() const;
    void setFrequency(int frequency);
    int getFrequency() const;
    int getNbPlayers() const;
    int getNbTeams() const;
    int getNbEggs() const;
    int getNbFood() const;
    int getNbLinemate() const;
    int getNbDeraumere() const;
    int getNbSibur() const;
    int getNbMendiane() const;
    int getNbPhiras() const;
    int getNbThystame() const;

    std::vector<std::vector<Tile_t>> getTiles() const;
    Tile_t getTile(int x, int y) const;
    void addPlayer(int x, int y, Player player);
    void delPlayer(int x, int y, Player player);
    void addEgg(int x, int y, Egg egg);
    void delEgg(int x, int y, Egg egg);
    void addFood(int x, int y);
    void delFood(int x, int y);
    void addLinemate(int x, int y);
    void delLinemate(int x, int y);
    void addDeraumere(int x, int y);
    void delDeraumere(int x, int y);
    void addSibur(int x, int y);
    void delSibur(int x, int y);
    void addMendiane(int x, int y);
    void delMendiane(int x, int y);
    void addPhiras(int x, int y);
    void delPhiras(int x, int y);
    void addThystame(int x, int y);
    void delThystame(int x, int y);

    void draw();
    void drawTransparent();
    bool selectTile(Ray ray);
    Tile_t getSelectedTile() const;

    void unload();
private:
    int _width;
    int _height;
    int _frequency;

    int _nbPlayers = 0;
    int _nbTeams = 0;
    int _nbEggs = 0;
    int _nbFood = 0;
    int _nbLinemate = 0;
    int _nbDeraumere = 0;
    int _nbSibur = 0;
    int _nbMendiane = 0;
    int _nbPhiras = 0;
    int _nbThystame = 0;

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
