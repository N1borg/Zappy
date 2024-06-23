/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Camera
*/

#pragma once

#include "RaylibWrapper.hpp"

class CameraObject {
    public:
        CameraObject();
        ~CameraObject() = default;

        Camera3D *getCameraObj() const;
        int getCameraMode() const;

        void setCameraMode(int cameraMode);
        void setCameraPosition(Vector3 position);
        void setCameraTarget(Vector3 target);
        void setCameraUp(Vector3 up);
        void setCameraFovy(float fovy);
        void setCameraProjection(int projection);

    private:
        int _cameraMode;
        Camera3D *_cameraObj;
};
