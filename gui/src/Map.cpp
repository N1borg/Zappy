/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** Map
*/

#include "Map.hpp"

Map::Map(int width, int height) : _width(width), _height(height)
{
    _isGameRunning = true;
    _nbPlayers = 0;
    _nbEggs = 0;
    _nbFood = 0;
    _nbLinemate = 0;
    _nbDeraumere = 0;
    _nbSibur = 0;
    _nbMendiane = 0;
    _nbPhiras = 0;
    _nbThystame = 0;

    _modelPlayer = LoadModel("gui/resources/player.glb");
    _modelEgg = LoadModel("gui/resources/egg.glb");
    _modelFood = LoadModel("gui/resources/food.glb");
    _modelLinemate = LoadModel("gui/resources/linemate.glb");
    _modelDeraumere = LoadModel("gui/resources/deraumere.glb");
    _modelSibur = LoadModel("gui/resources/sibur.glb");
    _modelMendiane = LoadModel("gui/resources/mendiane.glb");
    _modelPhiras = LoadModel("gui/resources/phiras.glb");
    _modelThystame = LoadModel("gui/resources/thystame.glb");
    _modelIsland = LoadModel("gui/resources/island.glb");
    _modelGrass = LoadModel("gui/resources/grass.glb");

    srand(time(0));

    for (int i = 0; i < width; i++) {
        std::vector<Tile_t> row;
        for (int j = 0; j < height; j++) {
            Tile_t tile(j, i, _modelFood, _modelLinemate, _modelDeraumere,
                        _modelSibur, _modelMendiane, _modelPhiras,
                        _modelThystame, _modelIsland, _modelGrass);
            int shift = GetRandomValue(1, 6);

            tile.island.first.setRotationY(GetRandomValue(0, 360) * DEG2RAD);
            tile.grass.first.setRotationY(GetRandomValue(0, 360) * DEG2RAD);
            tile.food.first.setRotationY(GetRandomValue(0, 360) * DEG2RAD);
            tile.linemate.first.setRotationY(GetRandomValue(0, 360) * DEG2RAD);
            tile.deraumere.first.setRotationY(GetRandomValue(0, 360) * DEG2RAD);
            tile.sibur.first.setRotationY(GetRandomValue(0, 360) * DEG2RAD);
            tile.mendiane.first.setRotationY(GetRandomValue(0, 360) * DEG2RAD);
            tile.phiras.first.setRotationY(GetRandomValue(0, 360) * DEG2RAD);
            tile.thystame.first.setRotationY(GetRandomValue(0, 360) * DEG2RAD);

            tile.food.first.setIslandPosition(GetRandomValue(0, 3));
            tile.linemate.first.setIslandPosition((1 + shift) % 6);
            tile.deraumere.first.setIslandPosition((2 + shift) % 6);
            tile.sibur.first.setIslandPosition((3 + shift) % 6);
            tile.mendiane.first.setIslandPosition((4 + shift) % 6);
            tile.phiras.first.setIslandPosition((5 + shift) % 6);
            tile.thystame.first.setIslandPosition((6 + shift) % 6);

            row.push_back(tile);
        }
        _tiles.push_back(row);
    }
}

int Map::getWidth() const
{
    return _width;
}

int Map::getHeight() const
{
    return _height;
}

bool Map::isGameRunning() const
{
    return _isGameRunning;
}

bool Map::isTileSelected() const
{
    return _isTileSelected;
}

void Map::setGameRunning(bool isGameRunning)
{
    _isGameRunning = isGameRunning;
}

int Map::getNbPlayers() const
{
    return _nbPlayers;
}

int Map::getNbEggs() const
{
    return _nbEggs;
}

int Map::getNbFood() const
{
    return _nbFood;
}

int Map::getNbLinemate() const
{
    return _nbLinemate;
}

int Map::getNbDeraumere() const
{
    return _nbDeraumere;
}

int Map::getNbSibur() const
{
    return _nbSibur;
}

int Map::getNbMendiane() const
{
    return _nbMendiane;
}

int Map::getNbPhiras() const
{
    return _nbPhiras;
}

int Map::getNbThystame() const
{
    return _nbThystame;
}

std::vector<std::vector<Tile_t>> Map::getTiles() const
{
    return _tiles;
}

Tile_t Map::getTile(int x, int y) const
{
    return _tiles[x][y];
}

// void Map::addPlayer(int id, int x, int y, Orientation orientation, int level, std::string team)
// {
//     for (Player p : _tiles[x][y].players) {
//         if (p.getId() == id)
//             return;
//     }
//     for (size_t i = 0; i < _teams.size(); i++) {
//         if (_teams[i].getTeamName() == team) {
//             Player player(_modelPlayer, id, x, y, orientation, _teams[i]);
//             player.setLevel(level);
//             _tiles[x][y].players.push_back(player);
//             _nbPlayers += 1;
//             _players.push_back(player);
//             _teams[i].setNumberPlayers(_teams[i].getNumberPlayers() + 1);
//         }
//     }
// }

void Map::movePlayer(int id, int x, int y, Orientation orientation)
{
    for (std::size_t i = 0; i < _players.size(); i++) {
        if (_players[i].getId() == id) {
            for (std::size_t j = 0; j < _tiles[_players[i].getX()][_players[i].getY()].players.size(); j++) {
                if (_tiles[_players[i].getX()][_players[i].getY()].players[j].getId() == id) {
                    _tiles[_players[i].getX()][_players[i].getY()].players.erase(_tiles[_players[i].getX()][_players[i].getY()].players.begin() + j);
                    _tiles[x][y].players.push_back(_players[i]);
                    _players[i].setX(x);
                    _players[i].setY(y);
                    _players[i].setOrientation(orientation);
                }
            }
        }
    }
}

void Map::delPlayer(int id)
{
    for (std::size_t i = 0; i < _players.size(); i++) {
        if (_players[i].getId() == id) {
            for (std::size_t j = 0; j < _tiles[_players[i].getX()][_players[i].getY()].players.size(); j++) {
                if (_tiles[_players[i].getX()][_players[i].getY()].players[j].getId() == id) {
                    _tiles[_players[i].getX()][_players[i].getY()].players.erase(_tiles[_players[i].getX()][_players[i].getY()].players.begin() + j);
                    _nbPlayers -= 1;
                    _players[i].getTeam().setNumberPlayers(_players[i].getTeam().getNumberPlayers() - 1);
                }
            }
            _players.erase(_players.begin() + i);
        }
    }
}

// void Map::addEgg(int id, int playerId, int x, int y, std::string team)
// {
//     for (Egg e : _tiles[x][y].eggs) {
//         if (e.getId() == id)
//             return;
//     }
//     for (size_t i = 0; i < _teams.size(); i++) {
//         if (_teams[i].getTeamName() == team) {
//             Egg egg(_modelEgg, id, playerId, x, y, _teams[i]);
//             _tiles[x][y].eggs.push_back(egg);
//             _nbEggs += 1;
//             _teams[i].setNumberEggs(_teams[i].getNumberEggs() + 1);
//         }
//     }
// }

void Map::moveEgg(int id, int x, int y)
{
    for (std::size_t i = 0; i < _tiles.size(); i++) {
        for (std::size_t j = 0; j < _tiles[i].size(); j++) {
            for (std::size_t k = 0; k < _tiles[i][j].eggs.size(); k++) {
                if (_tiles[i][j].eggs[k].getId() == id) {
                    _tiles[i][j].eggs[k].setX(x);
                    _tiles[i][j].eggs[k].setY(y);
                }
            }
        }
    }
}

void Map::delEgg(int id)
{
    for (std::size_t i = 0; i < _tiles.size(); i++) {
        for (std::size_t j = 0; j < _tiles[i].size(); j++) {
            for (std::size_t k = 0; k < _tiles[i][j].eggs.size(); k++) {
                if (_tiles[i][j].eggs[k].getId() == id) {
                    _tiles[i][j].eggs.erase(_tiles[i][j].eggs.begin() + k);
                    _nbEggs -= 1;
                    _tiles[i][j].eggs[k].getTeam().setNumberEggs(_tiles[i][j].eggs[k].getTeam().getNumberEggs() - 1);
                }
            }
        }
    }
}

void Map::addFood(int x, int y)
{
    _tiles[x][y].food.second += 1;
    _nbFood += 1;
}

void Map::delFood(int x, int y)
{
    _tiles[x][y].food.second -= 1;
    _nbFood -= 1;
}

void Map::addLinemate(int x, int y)
{
    _tiles[x][y].linemate.second += 1;
    _nbLinemate += 1;
}

void Map::delLinemate(int x, int y)
{
    _tiles[x][y].linemate.second -= 1;
    _nbLinemate -= 1;
}

void Map::addDeraumere(int x, int y)
{
    _tiles[x][y].deraumere.second += 1;
    _nbDeraumere += 1;
}

void Map::delDeraumere(int x, int y)
{
    _tiles[x][y].deraumere.second -= 1;
    _nbDeraumere -= 1;
}

void Map::addSibur(int x, int y)
{
    _tiles[x][y].sibur.second += 1;
    _nbSibur += 1;
}

void Map::delSibur(int x, int y)
{
    _tiles[x][y].sibur.second -= 1;
    _nbSibur -= 1;
}

void Map::addMendiane(int x, int y)
{
    _tiles[x][y].mendiane.second += 1;
    _nbMendiane += 1;
}

void Map::delMendiane(int x, int y)
{
    _tiles[x][y].mendiane.second -= 1;
    _nbMendiane -= 1;
}

void Map::addPhiras(int x, int y)
{
    _tiles[x][y].phiras.second += 1;
    _nbPhiras += 1;
}

void Map::delPhiras(int x, int y)
{
    _tiles[x][y].phiras.second -= 1;
    _nbPhiras -= 1;
}

void Map::addThystame(int x, int y)
{
    _tiles[x][y].thystame.second += 1;
    _nbThystame += 1;
}

void Map::delThystame(int x, int y)
{
    _tiles[x][y].thystame.second -= 1;
    _nbThystame -= 1;
}

void Map::setWidth(int width)
{
    _width = width;
}

void Map::setHeight(int height)
{
    _height = height;
}

void Map::draw()
{
    double time = GetTime();

    for (int x = 0; x < _width; x++) {
        for (int z = 0; z < _height; z++) {
            float blockScale = (x + 0.0f + z) / 40.0f;
            float scatter = sinf(blockScale * 20.0f + (float)(time * 2.0f));
            Tile_t& tile = _tiles[x][z];

            if (tile.island.second && tile.island.first.isSelected())
                continue;
            if (tile.island.second) {
                tile.island.first.draw({x * 10.0f, scatter, z * 10.0f}, 12.0f, WHITE);
                tile.island.first.drawWires({x * 10.0f, scatter, z * 10.0f}, 12.0f, BLACK);
            }
            for (Player player : tile.players) {
                player.draw({x * 10.0f, 9.0f + scatter, z * 10.0f}, 0.1f, player.getTeam().getTeamColor());
                player.drawWires({x * 10.0f, 9.0f + scatter, z * 10.0f}, 0.1f, BLACK);
            }
            if (tile.food.second) {
                tile.food.first.draw({x * 10.0f + tile.food.first.getIslandPositionX(), 8.91f + scatter, z * 10.0f + tile.food.first.getIslandPositionZ()}, 0.1f, WHITE);
                tile.food.first.drawWires({x * 10.0f + tile.food.first.getIslandPositionX(), 8.91f + scatter, z * 10.0f + tile.food.first.getIslandPositionZ()}, 0.1f, BLACK);
            }
            if (tile.linemate.second) {
                tile.linemate.first.draw({x * 10.0f + tile.linemate.first.getIslandPositionX(), 8.9f + scatter, z * 10.0f + tile.linemate.first.getIslandPositionZ()}, 20.0f, WHITE);
                tile.linemate.first.drawWires({x * 10.0f + tile.linemate.first.getIslandPositionX(), 8.9f + scatter, z * 10.0f + tile.linemate.first.getIslandPositionZ()}, 20.0f, BLACK);
            }
            if (tile.deraumere.second) {
                tile.deraumere.first.draw({x * 10.0f + tile.deraumere.first.getIslandPositionX(), 8.9f + scatter, z * 10.0f + tile.deraumere.first.getIslandPositionZ()}, 20.0f, WHITE);
                tile.deraumere.first.drawWires({x * 10.0f + tile.deraumere.first.getIslandPositionX(), 8.9f + scatter, z * 10.0f + tile.deraumere.first.getIslandPositionZ()}, 20.0f, BLACK);
            }
            if (tile.mendiane.second) {
                tile.mendiane.first.draw({x * 10.0f + tile.mendiane.first.getIslandPositionX(), 9.4f + scatter, z * 10.0f + tile.mendiane.first.getIslandPositionZ()}, 300.0f, WHITE);
                tile.mendiane.first.drawWires({x * 10.0f + tile.mendiane.first.getIslandPositionX(), 9.4f + scatter, z * 10.0f + tile.mendiane.first.getIslandPositionZ()}, 300.0f, BLACK);
            }
            for (Egg egg : tile.eggs) {
                egg.draw({x * 10.0f, 9.8f + scatter, z * 10.0f}, 5.0f, egg.getTeam().getTeamColor());
                egg.drawWires({x * 10.0f, 9.8f + scatter, z * 10.0f}, 5.0f, BLACK);
            }
            if (tile.grass.second)
                tile.grass.first.draw({x * 10.0f, 8.9f + scatter, z * 10.0f}, 3.0f, WHITE);
        }
    }
}

void Map::drawTransparent()
{
    double time = GetTime();

    for (int x = 0; x < _width; x++) {
        for (int z = 0; z < _height; z++) {
            float blockScale = (x + 0.0f + z) / 40.0f;
            float scatter = sinf(blockScale * 20.0f + (float)(time * 2.0f));
            Tile_t& tile = _tiles[x][z];
            float alpha = (sinf(time * 5.0f) + 1.0f) / 2.0f * 255.0f;
            bool isSelected = (tile.island.second && tile.island.first.isSelected());

            if (isSelected)
                tile.island.first.drawWires({x * 10.0f, scatter, z * 10.0f}, 12.0f, { 0, 0, 0, (unsigned char)alpha });
            for (Player player : tile.players) {
                if (isSelected)
                    player.drawWires({x * 10.0f, 9.0f + scatter, z * 10.0f}, 0.1f, { 0, 0, 0, (unsigned char)alpha });
            }
            if (tile.food.second && isSelected)
                tile.food.first.drawWires({x * 10.0f + tile.food.first.getIslandPositionX(), 8.91f + scatter, z * 10.0f + tile.food.first.getIslandPositionZ()}, 0.1f, { 0, 0, 0, (unsigned char)alpha });
            if (tile.linemate.second && isSelected)
                tile.linemate.first.drawWires({x * 10.0f + tile.linemate.first.getIslandPositionX(), 8.9f + scatter, z * 10.0f + tile.linemate.first.getIslandPositionZ()}, 20.0f, { 0, 0, 0, (unsigned char)alpha });
            if (tile.deraumere.second && isSelected)
                tile.deraumere.first.drawWires({x * 10.0f + tile.deraumere.first.getIslandPositionX(), 8.9f + scatter, z * 10.0f + tile.deraumere.first.getIslandPositionZ()}, 20.0f, { 0, 0, 0, (unsigned char)alpha });
            if (tile.sibur.second) {
                if (isSelected)
                    tile.sibur.first.drawWires({x * 10.0f + tile.sibur.first.getIslandPositionX(), 8.9f + scatter, z * 10.0f + tile.sibur.first.getIslandPositionZ()}, 55.0f, { 0, 0, 0, (unsigned char)alpha });
                else {
                    tile.sibur.first.draw({x * 10.0f + tile.sibur.first.getIslandPositionX(), 8.9f + scatter, z * 10.0f + tile.sibur.first.getIslandPositionZ()}, 55.0f, {255, 255, 255, 127});
                    tile.sibur.first.drawWires({x * 10.0f + tile.sibur.first.getIslandPositionX(), 8.9f + scatter, z * 10.0f + tile.sibur.first.getIslandPositionZ()}, 55.0f, BLACK);
                }
            }
            if (tile.mendiane.second && isSelected)
                tile.mendiane.first.drawWires({x * 10.0f + tile.mendiane.first.getIslandPositionX(), 9.4f + scatter, z * 10.0f + tile.mendiane.first.getIslandPositionZ()}, 300.0f, { 0, 0, 0, (unsigned char)alpha });
            if (tile.phiras.second) {
                if (isSelected)
                    tile.phiras.first.drawWires({x * 10.0f + tile.phiras.first.getIslandPositionX(), 9.3f + scatter, z * 10.0f + tile.phiras.first.getIslandPositionZ()}, 4.0f, { 0, 0, 0, (unsigned char)alpha });
                else {
                    tile.phiras.first.draw({x * 10.0f + tile.phiras.first.getIslandPositionX(), 9.3f + scatter, z * 10.0f + tile.phiras.first.getIslandPositionZ()}, 4.0f, {255, 255, 255, 200});
                    tile.phiras.first.drawWires({x * 10.0f + tile.phiras.first.getIslandPositionX(), 9.3f + scatter, z * 10.0f + tile.phiras.first.getIslandPositionZ()}, 4.0f, BLACK);
                }
            }
            if (tile.thystame.second) {
                if (isSelected)
                    tile.thystame.first.drawWires({x * 10.0f + tile.thystame.first.getIslandPositionX(), 8.9f + scatter, z * 10.0f + tile.thystame.first.getIslandPositionZ()}, 20.0f, { 0, 0, 0, (unsigned char)alpha });
                else {
                    tile.thystame.first.draw({x * 10.0f + tile.thystame.first.getIslandPositionX(), 8.9f + scatter, z * 10.0f + tile.thystame.first.getIslandPositionZ()}, 20.0f, {255, 255, 255, 200});
                    tile.thystame.first.drawWires({x * 10.0f + tile.thystame.first.getIslandPositionX(), 8.9f + scatter, z * 10.0f + tile.thystame.first.getIslandPositionZ()}, 20.0f, BLACK);
                }
            }
            for (Egg egg : tile.eggs) {
                if (isSelected)
                    egg.drawWires({x * 10.0f, 9.8f + scatter, z * 10.0f}, 5.0f, { 0, 0, 0, (unsigned char)alpha });
            }
            if (tile.grass.second && isSelected)
                tile.grass.first.drawWires({x * 10.0f, 8.9f + scatter, z * 10.0f}, 3.0f, { 0, 0, 0, (unsigned char)alpha });
        }
    }
}

bool Map::selectTile(Ray ray)
{
    RayCollision closestCollision;
    closestCollision.distance = FLT_MAX;
    bool hasHit = false;
    double time = GetTime();

    for (int x = 0; x < _width; x++) {
        for (int z = 0; z < _height; z++) {
            float blockScale = (x + 0.0f + z) / 40.0f;
            float scatter = sinf(blockScale * 20.0f + (float)(time * 2.0f));
            BoundingBox box = {
                { x * 10.0f - 4.9f, 0.0f + scatter, z * 10.0f - 4.9f }, // Min corner
                { x * 10.0f + 4.9f, 9.0f + scatter, z * 10.0f + 4.9f } // Max corner
            };

            RayCollision collision = GetRayCollisionBox(ray, box);
            if (collision.hit && collision.distance < closestCollision.distance) {
                closestCollision = collision;
                hasHit = true;
            }
        }
    }

    // Set selection status
    for (int x = 0; x < _width; x++) {
        for (int z = 0; z < _height; z++) {
            if (hasHit) {
                float blockScale = (x + 0.0f + z) / 40.0f;
                float scatter = sinf(blockScale * 20.0f + (float)(time * 2.0f));
                Tile_t& tile = _tiles[x][z];
                BoundingBox box = {
                    { x * 10.0f - 4.9f, 0.0f + scatter, z * 10.0f - 4.9f }, // Min corner
                    { x * 10.0f + 4.9f, 9.0f + scatter, z * 10.0f + 4.9f } // Max corner
                };

                RayCollision collision = GetRayCollisionBox(ray, box);
                if (collision.hit && collision.distance == closestCollision.distance && tile.island.first.isSelected() == false) {
                    tile.island.first.setSelected(true);
                    _isTileSelected = true;
                } else
                    tile.island.first.setSelected(false);
            } else
                _tiles[x][z].island.first.setSelected(false);
        }
    }
    return _isTileSelected;
}

Tile_t Map::getSelectedTile() const
{
    for (int x = 0; x < _width; x++) {
        for (int z = 0; z < _height; z++) {
            if (_tiles[x][z].island.first.isSelected())
                return _tiles[x][z];
        }
    }
    return _tiles[0][0];
}

void Map::unload()
{
    UnloadModel(_modelFood);
    UnloadModel(_modelLinemate);
    UnloadModel(_modelDeraumere);
    UnloadModel(_modelSibur);
    UnloadModel(_modelMendiane);
    UnloadModel(_modelPhiras);
    UnloadModel(_modelThystame);
    UnloadModel(_modelIsland);
    UnloadModel(_modelGrass);
}
