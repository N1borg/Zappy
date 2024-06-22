/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** Map
*/

#include "Map.hpp"

Map::Map(int width, int height) : _width(width), _height(height)
{
    _modelFood = LoadModel("gui/resources/food.glb");
    _modelLinemate = LoadModel("gui/resources/linemate.glb");
    _modelDeraumere = LoadModel("gui/resources/deraumere.glb");
    _modelSibur = LoadModel("gui/resources/sibur.glb");
    _modelMendiane = LoadModel("gui/resources/mendiane.glb");
    _modelPhiras = LoadModel("gui/resources/phiras.glb");
    _modelThystame = LoadModel("gui/resources/thystame.glb");
    _modelIsland = LoadModel("gui/resources/island.glb");
    _modelGrass = LoadModel("gui/resources/grass.glb");

    srand(time(NULL));

    for (int i = 0; i < width; i++) {
        std::vector<Tile_t> row;
        for (int j = 0; j < height; j++) {
            Tile_t tile(_modelFood, _modelLinemate, _modelDeraumere,
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

std::vector<std::vector<Tile_t>> Map::getTiles() const
{
    return _tiles;
}

Tile_t Map::getTile(int x, int y) const
{
    return _tiles[x][y];
}

void Map::setPlayer(int x, int y, Player player)
{
    _tiles[x][y].players.push_back(player);
}

void Map::setEgg(int x, int y, Egg egg)
{
    _tiles[x][y].eggs.push_back(egg);
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

void Map::setGrass(int x, int y, bool value)
{
    _tiles[x][y].grass.second = value;
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
                tile.linemate.first.draw({x * 10.0f + tile.linemate.first.getIslandPositionX(), 9.8f + scatter, z * 10.0f + tile.linemate.first.getIslandPositionZ()}, 20.0f, WHITE);
                tile.linemate.first.drawWires({x * 10.0f + tile.linemate.first.getIslandPositionX(), 9.8f + scatter, z * 10.0f + tile.linemate.first.getIslandPositionZ()}, 20.0f, BLACK);
            }
            if (tile.deraumere.second) {
                tile.deraumere.first.draw({x * 10.0f + tile.deraumere.first.getIslandPositionX(), 9.8f + scatter, z * 10.0f + tile.deraumere.first.getIslandPositionZ()}, 20.0f, WHITE);
                tile.deraumere.first.drawWires({x * 10.0f + tile.deraumere.first.getIslandPositionX(), 9.8f + scatter, z * 10.0f + tile.deraumere.first.getIslandPositionZ()}, 20.0f, BLACK);
            }
            if (tile.mendiane.second) {
                tile.mendiane.first.draw({x * 10.0f + tile.mendiane.first.getIslandPositionX(), 9.8f + scatter, z * 10.0f + tile.mendiane.first.getIslandPositionZ()}, 300.0f, WHITE);
                tile.mendiane.first.drawWires({x * 10.0f + tile.mendiane.first.getIslandPositionX(), 9.8f + scatter, z * 10.0f + tile.mendiane.first.getIslandPositionZ()}, 300.0f, BLACK);
            }
            if (tile.phiras.second) {
                tile.phiras.first.draw({x * 10.0f + tile.phiras.first.getIslandPositionX(), 9.8f + scatter, z * 10.0f + tile.phiras.first.getIslandPositionZ()}, 300.0f, WHITE);
                tile.phiras.first.drawWires({x * 10.0f + tile.phiras.first.getIslandPositionX(), 9.8f + scatter, z * 10.0f + tile.phiras.first.getIslandPositionZ()}, 300.0f, BLACK);
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
                tile.linemate.first.drawWires({x * 10.0f + tile.linemate.first.getIslandPositionX(), 9.8f + scatter, z * 10.0f + tile.linemate.first.getIslandPositionZ()}, 20.0f, { 0, 0, 0, (unsigned char)alpha });
            if (tile.deraumere.second && isSelected)
                tile.deraumere.first.drawWires({x * 10.0f + tile.deraumere.first.getIslandPositionX(), 9.8f + scatter, z * 10.0f + tile.deraumere.first.getIslandPositionZ()}, 20.0f, { 0, 0, 0, (unsigned char)alpha });
            if (tile.sibur.second) {
                if (isSelected)
                    tile.sibur.first.drawWires({x * 10.0f + tile.sibur.first.getIslandPositionX(), 9.8f + scatter, z * 10.0f + tile.sibur.first.getIslandPositionZ()}, 55.0f, { 0, 0, 0, (unsigned char)alpha });
                else {
                    tile.sibur.first.draw({x * 10.0f + tile.sibur.first.getIslandPositionX(), 9.8f + scatter, z * 10.0f + tile.sibur.first.getIslandPositionZ()}, 55.0f, {255, 255, 255, 127});
                    tile.sibur.first.drawWires({x * 10.0f + tile.sibur.first.getIslandPositionX(), 9.8f + scatter, z * 10.0f + tile.sibur.first.getIslandPositionZ()}, 55.0f, BLACK);
                }
            }
            if (tile.mendiane.second && isSelected)
                tile.mendiane.first.drawWires({x * 10.0f + tile.mendiane.first.getIslandPositionX(), 9.8f + scatter, z * 10.0f + tile.mendiane.first.getIslandPositionZ()}, 300.0f, { 0, 0, 0, (unsigned char)alpha });
            if (tile.phiras.second && isSelected)
                tile.phiras.first.drawWires({x * 10.0f + tile.phiras.first.getIslandPositionX(), 9.8f + scatter, z * 10.0f + tile.phiras.first.getIslandPositionZ()}, 300.0f, { 0, 0, 0, (unsigned char)alpha });
            if (tile.thystame.second) {
                if (isSelected)
                    tile.thystame.first.drawWires({x * 10.0f + tile.thystame.first.getIslandPositionX(), 9.8f + scatter, z * 10.0f + tile.thystame.first.getIslandPositionZ()}, 20.0f, { 0, 0, 0, (unsigned char)alpha });
                else {
                    tile.thystame.first.draw({x * 10.0f + tile.thystame.first.getIslandPositionX(), 9.8f + scatter, z * 10.0f + tile.thystame.first.getIslandPositionZ()}, 20.0f, {255, 255, 255, 200});
                    tile.thystame.first.drawWires({x * 10.0f + tile.thystame.first.getIslandPositionX(), 9.8f + scatter, z * 10.0f + tile.thystame.first.getIslandPositionZ()}, 20.0f, BLACK);
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
