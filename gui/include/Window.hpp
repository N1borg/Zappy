/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Window
*/

#pragma once

#include "Parser/ParseArguments.hpp"
#include "RaylibWrapper.hpp"
#include "Socket.hpp"

#include <raylib.h>
#include <math.h>
#include <string>

class Window {
    public:
        Window(int width, int height, std::string title);
        ~Window() = default;

        // Raylib window functions
        void init();

        // Raylib Camera functions
        Camera3D getCamera() const;
        int getCameraMode() const;
        void setCameraPosition(Vector3 position);
        void setCameraTarget(Vector3 target);
        void setCameraUp(Vector3 up);
        void setCameraFovy(float fovy);
        void setCameraProjection(int projection);
        void setCameraMode(int mode);
        void parseCameraInputs();

        // Raylib drawing functions
        void drawCrosshair();

        std::string animateTextDots(const std::string &string, float elapsedTime);
        int waitingConnection(Socket &socket, std::string ip, bool isReconnecting);
        void waitingScreen(float elapsedTime);
        void drawConnectionText(std::string ip, bool isReconnecting, int elapsedTime);

    private:
        int _width;
        int _height;
        std::string _title;
        Camera _camera;
        int _cameraMode;
};
