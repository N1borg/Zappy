/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Camera
*/

#include "Camera.hpp"

GameCamera::GameCamera()
{
    _camera = {0};
    _position = {0.0f, 10.0f, 10.0f};
    _target = {0.0f, 0.0f, 0.0f};
    _up = {0.0f, 1.0f, 0.0f};
    _fovy = 45.0f;
    _projection = CAMERA_PERSPECTIVE;
    updateCamera();
}

void GameCamera::setPosition(Vector3 position)
{
    _position = position;
}

void GameCamera::setTarget(Vector3 target)
{
    _target = target;
}

void GameCamera::setUp(Vector3 up)
{
    _up = up;
}

void GameCamera::setFovy(float fovy)
{
    _fovy = fovy;
}

void GameCamera::setProjection(int projection)
{
    _projection = projection;
}

void GameCamera::updateCamera()
{
    _camera.position = _position;
    _camera.target = _target;
    _camera.up = _up;
    _camera.fovy = _fovy;
    _camera.projection = _projection;
}

Camera3D GameCamera::getCamera() const
{
    return _camera;
}