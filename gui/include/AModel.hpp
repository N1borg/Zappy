/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** AModel
*/

#pragma once

#include "IModel.hpp"

class AModel : public IModel {
public:
    AModel(Model model);
    ~AModel() = default;

    Model getModel() const;
    void setIslandPosition(int islandPosition) override;
    int getIslandPositionX() const override;
    int getIslandPositionZ() const override;
    void setRotationY(float yRotation) override;

    void draw(Vector3 position, float scale, Color tint) const override;
    void drawWires(Vector3 position, float scale, Color tint) const override;
protected:
    Model _model;
    float _islandPositionX;
    float _islandPositionZ;
    float _yRotation;
};
