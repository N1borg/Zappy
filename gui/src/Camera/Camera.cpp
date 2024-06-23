/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Camera
*/

#include "Camera/Camera.hpp"

Camera3D CameraObject::getCameraObj() const
{
    return _cameraObj;
}

int CameraObject::getCameraMode() const
{
    return _cameraMode;
}

void CameraObject::setCameraMode(int cameraMode)
{
    _cameraMode = cameraMode;
}

void CameraObject::setCameraObj(Camera3D cameraObj)
{
    _cameraObj = cameraObj;
}

void CameraObject::setCameraPosition(Vector3 position)
{
    _cameraObj.position = position;
}

void CameraObject::setCameraTarget(Vector3 target)
{
    _cameraObj.target = target;
}

void CameraObject::setCameraUp(Vector3 up)
{
    _cameraObj.up = up;
}

void CameraObject::setCameraFovy(float fovy)
{
    _cameraObj.fovy = fovy;
}

void CameraObject::setCameraProjection(int projection)
{
    _cameraObj.projection = projection;
}
