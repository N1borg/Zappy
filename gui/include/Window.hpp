/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Window
*/

#pragma once

#include "Parser/ParseArguments.hpp"
#include "RaylibWrapper.hpp"
#include "Camera/Camera.hpp"
#include "Socket.hpp"

class Window {
    public:
        Window(int width, int height, std::string title);
        ~Window() = default;

        // Raylib window functions
        void init();

        // Raylib Camera functions
        CameraObject *getCamera();

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
        CameraObject *_camera;
        CameraObject *_minimap;
};
