/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Map
*/

#pragma once

#include "Models/Player.hpp"
#include "Models/Collectables/Egg.hpp"
#include "Models/Collectables/Food.hpp"
#include "Models/Collectables/Linemate.hpp"
#include "Models/Collectables/Deraumere.hpp"
#include "Models/Collectables/Sibur.hpp"
#include "Models/Collectables/Mendiane.hpp"
#include "Models/Collectables/Phiras.hpp"
#include "Models/Collectables/Thystame.hpp"
#include "Models/Island.hpp"
#include "Models/Grass.hpp"

#include <math.h>
#include <time.h>
#include <deque>
#include <vector>
#include <cfloat>

typedef struct Tile_s {
    int xPos;
    int yPos;
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

    Tile_s(int x, int y, Model _modelFood, Model _modelLinemate, Model _modelDeraumere,
        Model _modelSibur, Model _modelMendiane, Model _modelPhiras,
        Model _modelThystame, Model _modelIsland, Model _modelGrass)
            : xPos(x), yPos(y), food(std::make_pair(Food(_modelFood), 0)),
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
    Map(int width, int height, int frequency, std::vector<Team> teams);
    ~Map() = default;

    int getWidth() const { return _width; }
    int getHeight() const { return _height; }
    void setFrequency(int frequency) { _frequency = frequency; }
    int getFrequency() const { return _frequency; }
    void setGameRunning(bool isGameRunning) { _isGameRunning = isGameRunning; }
    bool isGameRunning() const { return _isGameRunning; }
    int getNbPlayers() const { return _nbPlayer; }
    int getNbTeams() const { return _nbTeam; }
    int getNbEggs() const { return _nbEgg; }
    int getNbFood() const { return _nbFood; }
    int getNbLinemate() const { return _nbLinemate; }
    int getNbDeraumere() const { return _nbDeraumere; }
    int getNbSibur() const { return _nbSibur; }
    int getNbMendiane() const { return _nbMendiane; }
    int getNbPhiras() const { return _nbPhiras; }
    int getNbThystame() const { return _nbThystame; }

    std::vector<std::vector<Tile_t>> getTiles() const { return _tiles; }
    Tile_t getTile(int x, int y) const { return _tiles[x][y]; }
    std::vector<Team> getTeams() const { return _teams; }
    Color getTeamColor(std::string team) const;
    Team getTeamByPlayerId(int id) const;
    std::vector<Player> getPlayers() const { return _players; }
    Player getPlayerById(int id) const;
    std::vector<Egg> getEggs() const;
    Egg getEggById(int id) const;
    void addPlayer(int id, int x, int y, Orientation orientation, int level, std::string team);
    void movePlayer(int id, int x, int y, Orientation orientation);
    void delPlayer(int id);
    void addEgg(int id, int playerId, int x, int y, std::string team);
    void moveEgg(int id, int x, int y);
    void delEgg(int id);
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
    bool _isGameRunning;

    int _nbPlayer;
    int _nbTeam;
    int _nbEgg;
    int _nbFood;
    int _nbLinemate;
    int _nbDeraumere;
    int _nbSibur;
    int _nbMendiane;
    int _nbPhiras;
    int _nbThystame;

    std::vector<Team> _teams;
    std::vector<Player> _players;

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
