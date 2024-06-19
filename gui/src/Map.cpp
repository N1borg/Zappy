/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** Map
*/

#include "Map.hpp"

Map::Map(int width, int height) : _width(width), _height(height)
{
    _modelPlayer = LoadModel("gui/ressources/player.glb");
    _modelEgg = LoadModel("gui/ressources/egg.glb");
    _modelFood = LoadModel("gui/ressources/food.glb");
    _modelLinemate = LoadModel("gui/ressources/linemate.glb");
    _modelDeraumere = LoadModel("gui/ressources/deraumere.glb");
    _modelSibur = LoadModel("gui/ressources/sibur.glb");
    _modelMendiane = LoadModel("gui/ressources/mendiane.glb");
    _modelPhiras = LoadModel("gui/ressources/phiras.glb");
    _modelThystame = LoadModel("gui/ressources/thystame.glb");
    _modelSmallIsland = LoadModel("gui/ressources/small_island.glb");
    _modelMediumIsland = LoadModel("gui/ressources/medium_island.glb");
    _modelBigIsland = LoadModel("gui/ressources/big_island.glb");

    srand(time(NULL));

    for (int i = 0; i < width; i++) {
        std::vector<Tile_t> row;
        for (int j = 0; j < height; j++) {
            Tile_t tile(_modelPlayer, _modelEgg, _modelFood, _modelLinemate, _modelDeraumere, _modelSibur,
                _modelMendiane, _modelPhiras, _modelThystame, _modelSmallIsland, _modelMediumIsland, _modelBigIsland);

            tile.player.first.setRotationY(GetRandomValue(0, 360) * DEG2RAD);
            tile.food.first.setRotationY(GetRandomValue(0, 360) * DEG2RAD);
            tile.linemate.first.setRotationY(GetRandomValue(0, 360) * DEG2RAD);
            tile.deraumere.first.setRotationY(GetRandomValue(0, 360) * DEG2RAD);
            tile.sibur.first.setRotationY(GetRandomValue(0, 360) * DEG2RAD);
            tile.mendiane.first.setRotationY(GetRandomValue(0, 360) * DEG2RAD);
            tile.phiras.first.setRotationY(GetRandomValue(0, 360) * DEG2RAD);
            tile.thystame.first.setRotationY(GetRandomValue(0, 360) * DEG2RAD);
            tile.smallIsland.first.setRotationY(GetRandomValue(0, 360) * DEG2RAD);

            row.push_back(tile);
        }
        _tiles.push_back(row);
    }
}

std::vector<std::vector<Tile_t>> Map::getTiles() const
{
    return _tiles;
}

void Map::draw()
{
    double time = GetTime();

    for (int x = 0; x < _width; x++) {
        for (int z = 0; z < _height; z++) {
            float blockScale = (x + 0.0f + z) / 40.0f;
            float scatter = sinf(blockScale * 20.0f + (float)(time * 2.0f));

            Tile_t& tile = _tiles[x][z];

            if (tile.smallIsland.second)
                tile.smallIsland.first.draw({x * 10.0f, scatter, z * 10.0f}, 12.0f, WHITE);
            if (tile.player.second)
                tile.player.first.draw({x * 10.0f, 9.0f + scatter, z * 10.0f}, 0.1f, WHITE);
            if (tile.food.second)
                tile.food.first.draw({x * 10.0f, 8.91f + scatter, z * 10.0f}, 0.1f, WHITE);
            if (tile.linemate.second)
                tile.linemate.first.draw({x * 10.0f, 9.8f + scatter, z * 10.0f}, 20.0f, WHITE);
            if (tile.deraumere.second)
                tile.deraumere.first.draw({x * 10.0f, 9.8f + scatter, z * 10.0f}, 20.0f, WHITE);
            if (tile.sibur.second)
                tile.sibur.first.draw({x * 10.0f, 9.8f + scatter, z * 10.0f}, 55.0f, WHITE);
            if (tile.mendiane.second)
                tile.mendiane.first.draw({x * 10.0f, 9.8f + scatter, z * 10.0f}, 300.0f, WHITE);
            if (tile.phiras.second)
                tile.phiras.first.draw({x * 10.0f, 9.8f + scatter, z * 10.0f}, 300.0f, WHITE);
            if (tile.thystame.second)
                tile.thystame.first.draw({x * 10.0f, 9.8f + scatter, z * 10.0f}, 20.0f, WHITE);
            if (tile.egg.second)
                tile.egg.first.draw({x * 10.0f, 9.8f + scatter, z * 10.0f}, 5.0f, WHITE);
        }
    }
}

void Map::setPlayer(int x, int y, bool value)
{
    _tiles[x][y].player.second = value;
}

void Map::setEgg(int x, int y, bool value)
{
    _tiles[x][y].egg.second = value;
}

void Map::setFood(int x, int y, bool value)
{
    _tiles[x][y].food.second = value;
}

void Map::setLinemate(int x, int y, bool value)
{
    _tiles[x][y].linemate.second = value;
}

void Map::setDeraumere(int x, int y, bool value)
{
    _tiles[x][y].deraumere.second = value;
}

void Map::setSibur(int x, int y, bool value)
{
    _tiles[x][y].sibur.second = value;
}

void Map::setMendiane(int x, int y, bool value)
{
    _tiles[x][y].mendiane.second = value;
}

void Map::setPhiras(int x, int y, bool value)
{
    _tiles[x][y].phiras.second = value;
}

void Map::setThystame(int x, int y, bool value)
{
    _tiles[x][y].thystame.second = value;
}

void Map::setSmallIsland(int x, int y, bool value)
{
    _tiles[x][y].smallIsland.second = value;
}

void Map::setMediumIsland(int x, int y, bool value)
{
    _tiles[x][y].mediumIsland.second = value;
}

void Map::setBigIsland(int x, int y, bool value)
{
    _tiles[x][y].bigIsland.second = value;
}

void Map::unload()
{
    UnloadModel(_modelPlayer);
    UnloadModel(_modelEgg);
    UnloadModel(_modelFood);
    UnloadModel(_modelLinemate);
    UnloadModel(_modelDeraumere);
    UnloadModel(_modelSibur);
    UnloadModel(_modelMendiane);
    UnloadModel(_modelPhiras);
    UnloadModel(_modelThystame);
    UnloadModel(_modelSmallIsland);
    UnloadModel(_modelMediumIsland);
    UnloadModel(_modelBigIsland);
}
