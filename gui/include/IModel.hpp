/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** Model
*/

#pragma once

#include <raylib.h>
#include <raymath.h>

class IModel {
public:
    virtual ~IModel() = default;

    virtual void draw(Vector3 position, float scale, Color tint) const = 0;
    virtual void drawWires(Vector3 position, float scale, Color tint) const = 0;

    virtual void setIslandPosition(int islandPosition) = 0;
    virtual int getIslandPositionX() const = 0;
    virtual int getIslandPositionZ() const = 0;
    virtual void setRotationY(float yRotation) = 0;
};
