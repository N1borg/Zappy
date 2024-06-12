/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Camera
*/

#include "Camera.hpp"

GameCamera::GameCamera()
{
    _camera = {
        {0.0f, 10.0f, 10.0f}, // Camera position
        {0.0f, 0.0f, 0.0f}, // Camera target
        {0.0f, 1.0f, 0.0f}, // Camera up vector
        45.0f, // Camera field-of-view Y
        CAMERA_PERSPECTIVE // Camera mode type
    };
}

void GameCamera::setPosition(Vector3 position)
{
    _camera.position = position;
}

void GameCamera::setTarget(Vector3 target)
{
    _camera.target = target;
}

void GameCamera::setUp(Vector3 up)
{
    _camera.up = up;
}

void GameCamera::setFovy(float fovy)
{
    _camera.fovy = fovy;
}

void GameCamera::setProjection(int projection)
{
    _camera.projection = projection;
}

Camera3D GameCamera::getCamera() const
{
    return _camera;
}