/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** AModel
*/

#pragma once

#include "IModel.hpp"

class AModel : public IModel {
public:
    AModel(Model model) : _model(model), _islandPositionX(0.0f), _islandPositionZ(0.0f), _yRotation(0.0f) {}
    ~AModel() = default;

    Model getModel() const { return _model; }
    int getIslandPositionX() const override { return _islandPositionX; }
    int getIslandPositionZ() const override { return _islandPositionZ; }
    void setIslandPosition(int islandPosition) override;
    void setRotationY(float yRotation) override { _yRotation = yRotation; }

    void draw(Vector3 position, float scale, Color tint) const override;
    void drawWires(Vector3 position, float scale, Color tint) const override;
protected:
    Model _model;
    float _islandPositionX;
    float _islandPositionZ;
    float _yRotation;
};
