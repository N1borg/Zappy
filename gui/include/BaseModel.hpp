/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** BaseModel
*/

#pragma once

#include "IModel.hpp"

class BaseModel : public IModel {
public:
    BaseModel(Model model);
    ~BaseModel() = default;

    void draw(Vector3 position, float scale, Color tint) const override;
    void drawWires(Vector3 position, float scale, Color tint) const override;

    void setRotationY(float yRotation) override;

protected:
    Model _model;
    float _yRotation;
};