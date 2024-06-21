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
    _modelIsland = LoadModel("gui/ressources/island.glb");

    srand(time(NULL));

    for (int i = 0; i < width; i++) {
        std::vector<Tile_t> row;
        for (int j = 0; j < height; j++) {
            Tile_t tile(_modelPlayer, _modelEgg, _modelFood, _modelLinemate, _modelDeraumere, _modelSibur,
                _modelMendiane, _modelPhiras, _modelThystame, _modelIsland);

            tile.player.first.setRotationY(GetRandomValue(0, 4) * 90 * DEG2RAD);
            tile.food.first.setRotationY(GetRandomValue(0, 360) * DEG2RAD);
            tile.linemate.first.setRotationY(GetRandomValue(0, 360) * DEG2RAD);
            tile.deraumere.first.setRotationY(GetRandomValue(0, 360) * DEG2RAD);
            tile.sibur.first.setRotationY(GetRandomValue(0, 360) * DEG2RAD);
            tile.mendiane.first.setRotationY(GetRandomValue(0, 360) * DEG2RAD);
            tile.phiras.first.setRotationY(GetRandomValue(0, 360) * DEG2RAD);
            tile.thystame.first.setRotationY(GetRandomValue(0, 360) * DEG2RAD);
            tile.island.first.setRotationY(GetRandomValue(0, 360) * DEG2RAD);

            row.push_back(tile);
        }
        _tiles.push_back(row);
    }
}

std::vector<std::vector<Tile_t>> Map::getTiles() const
{
    return _tiles;
}

Tile_t Map::getTile(int x, int y) const
{
    return _tiles[x][y];
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

void Map::setIsland(int x, int y, bool value)
{
    _tiles[x][y].island.second = value;
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
            if (tile.player.second) {
                tile.player.first.draw({x * 10.0f, 9.0f + scatter, z * 10.0f}, 0.1f, VIOLET);
                tile.player.first.drawWires({x * 10.0f, 9.0f + scatter, z * 10.0f}, 0.1f, BLACK);
            }
            if (tile.food.second) {
                tile.food.first.draw({x * 10.0f, 8.91f + scatter, z * 10.0f}, 0.1f, WHITE);
                tile.food.first.drawWires({x * 10.0f, 8.91f + scatter, z * 10.0f}, 0.1f, BLACK);
            }
            if (tile.linemate.second) {
                tile.linemate.first.draw({x * 10.0f, 9.8f + scatter, z * 10.0f}, 20.0f, WHITE);
                tile.linemate.first.drawWires({x * 10.0f, 9.8f + scatter, z * 10.0f}, 20.0f, BLACK);
            }
            if (tile.deraumere.second) {
                tile.deraumere.first.draw({x * 10.0f, 9.8f + scatter, z * 10.0f}, 20.0f, WHITE);
                tile.deraumere.first.drawWires({x * 10.0f, 9.8f + scatter, z * 10.0f}, 20.0f, BLACK);
            }
            if (tile.mendiane.second) {
                tile.mendiane.first.draw({x * 10.0f, 9.8f + scatter, z * 10.0f}, 300.0f, WHITE);
                tile.mendiane.first.drawWires({x * 10.0f, 9.8f + scatter, z * 10.0f}, 300.0f, BLACK);
            }
            if (tile.phiras.second) {
                tile.phiras.first.draw({x * 10.0f, 9.8f + scatter, z * 10.0f}, 300.0f, WHITE);
                tile.phiras.first.drawWires({x * 10.0f, 9.8f + scatter, z * 10.0f}, 300.0f, BLACK);
            }
            if (tile.egg.second) {
                tile.egg.first.draw({x * 10.0f, 9.8f + scatter, z * 10.0f}, 5.0f, VIOLET);
                tile.egg.first.drawWires({x * 10.0f, 9.8f + scatter, z * 10.0f}, 5.0f, BLACK);
            }
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
            if (tile.player.second && isSelected)
                tile.player.first.drawWires({x * 10.0f, 9.0f + scatter, z * 10.0f}, 0.1f, { 0, 0, 0, (unsigned char)alpha });
            if (tile.food.second && isSelected)
                tile.food.first.drawWires({x * 10.0f, 8.91f + scatter, z * 10.0f}, 0.1f, { 0, 0, 0, (unsigned char)alpha });
            if (tile.linemate.second && isSelected)
                tile.linemate.first.drawWires({x * 10.0f, 9.8f + scatter, z * 10.0f}, 20.0f, { 0, 0, 0, (unsigned char)alpha });
            if (tile.deraumere.second)
                tile.deraumere.first.drawWires({x * 10.0f, 9.8f + scatter, z * 10.0f}, 20.0f, { 0, 0, 0, (unsigned char)alpha });
            if (tile.sibur.second) {
                if (isSelected)
                    tile.sibur.first.drawWires({x * 10.0f, 9.8f + scatter, z * 10.0f}, 55.0f, { 0, 0, 0, (unsigned char)alpha });
                else {
                    tile.sibur.first.draw({x * 10.0f, 9.8f + scatter, z * 10.0f}, 55.0f, {255, 255, 255, 127});
                    tile.sibur.first.drawWires({x * 10.0f, 9.8f + scatter, z * 10.0f}, 55.0f, BLACK);
                }
            }
            if (tile.mendiane.second)
                tile.mendiane.first.drawWires({x * 10.0f, 9.8f + scatter, z * 10.0f}, 300.0f, { 0, 0, 0, (unsigned char)alpha });
            if (tile.phiras.second)
                tile.phiras.first.drawWires({x * 10.0f, 9.8f + scatter, z * 10.0f}, 300.0f, { 0, 0, 0, (unsigned char)alpha });
            if (tile.thystame.second) {
                if (isSelected)
                    tile.thystame.first.drawWires({x * 10.0f, 9.8f + scatter, z * 10.0f}, 20.0f, { 0, 0, 0, (unsigned char)alpha });
                else {
                    tile.thystame.first.draw({x * 10.0f, 9.8f + scatter, z * 10.0f}, 20.0f, {255, 255, 255, 200});
                    tile.thystame.first.drawWires({x * 10.0f, 9.8f + scatter, z * 10.0f}, 20.0f, BLACK);
                }
            }
            if (tile.egg.second)
                tile.egg.first.drawWires({x * 10.0f, 9.8f + scatter, z * 10.0f}, 5.0f, { 0, 0, 0, (unsigned char)alpha });
        }
    }
}

void Map::selectTile(Ray ray)
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
                if (collision.hit && collision.distance == closestCollision.distance && tile.island.first.isSelected() == false)
                    tile.island.first.setSelected(true);
                else
                    tile.island.first.setSelected(false);
            } else
                _tiles[x][z].island.first.setSelected(false);
        }
    }
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
    UnloadModel(_modelIsland);
}
