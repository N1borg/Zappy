/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Camera
*/

#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include <raylib.h>

class GameCamera {
    public:
        GameCamera();
        ~GameCamera() = default;

        Camera3D getCamera() const;
        void updateCamera();

        // Update functions for the camera
        void setPosition(Vector3 position);
        void setTarget(Vector3 target);
        void setUp(Vector3 up);
        void setFovy(float fovy);
        void setProjection(int projection);

    private:
        Camera3D _camera;
        Vector3 _position;
        Vector3 _target;
        Vector3 _up;
        float _fovy;
        int _projection;
};

#endif /* !CAMERA_HPP_ */
