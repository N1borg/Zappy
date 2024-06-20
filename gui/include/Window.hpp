/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Window
*/

#pragma once

#include <raylib.h>
#include <math.h>
#include <string>

#include "Parser/ParseArguments.hpp"
#include "Socket.hpp"

class Window {
    public:
        Window(int width, int height, std::string title);
        ~Window() = default;

        // Raylib window functions
        void init();
        void close();
        bool shouldClose();
        void setTargetFPS(int fps);
        int getScreenWidth() const;
        int getScreenHeight() const;
        void disableCursor();
        bool isKeyPressed(int key);

        // Raylib Camera functions
        Camera3D getCamera() const;
        int getCameraMode() const;
        void updateCamera();
        void setCameraPosition(Vector3 position);
        void setCameraTarget(Vector3 target);
        void setCameraUp(Vector3 up);
        void setCameraFovy(float fovy);
        void setCameraProjection(int projection);
        void setCameraMode(int mode);
        void parseCameraInputs();

        // Raylib drawing functions
        void beginDrawing();
        void endDrawing();
        void beginMode3D();
        void endMode3D();
        void clearBackground(Color color);
        void drawPlane(Vector3 position, Vector2 size, Color color);
        void drawGrid(int slices, float spacing);
        void drawText(const char *text, int posX, int posY, int fontSize, Color color);
        void drawFPS(int posX, int posY);

        std::string animateTextDots(const std::string &string, float elapsedTime);
        int drawWaitingScreen(Socket &socket, ParseArguments &argsParser);
        void drawConnection(bool isConnected, std::string ip, int elapsedTime);

    private:
        int _width;
        int _height;
        std::string _title;
        Camera _camera;
        int _cameraMode;
};
