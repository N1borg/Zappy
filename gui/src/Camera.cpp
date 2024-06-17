/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Camera
*/

#include "Camera.hpp"

GameCamera::GameCamera()
{
    _position = {0.0f, 10.0f, 10.0f};
    _target = {0.0f, 0.0f, 0.0f};
    _up = {0.0f, 1.0f, 0.0f};
    _fovy = 45.0f;
    _projection = CAMERA_PERSPECTIVE;
    _mode = CAMERA_THIRD_PERSON;
}

void GameCamera::updateCamera()
{
    UpdateCamera(&_camera, _mode);
}

Camera3D GameCamera::getCamera() const
{
    return _camera;
}

void GameCamera::setPosition(Vector3 position)
{
    _position = position;
    _camera.position = _position;
}

void GameCamera::setTarget(Vector3 target)
{
    _target = target;
    _camera.target = _target;
}

void GameCamera::setUp(Vector3 up)
{
    _up = up;
    _camera.up = _up;
}

void GameCamera::setFovy(float fovy)
{
    _fovy = fovy;
    _camera.fovy = _fovy;
}

void GameCamera::setProjection(int projection)
{
    _projection = projection;
    _camera.projection = _projection;
}

void GameCamera::setMode(CameraMode mode)
{
    _mode = mode;
}
