/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Window
*/

#pragma once

#include <raylib.h>
#include <string>

#include "Camera.hpp"

class Window {
    public:
        Window() = default;
        Window(int width, int height, std::string title);
        ~Window() = default;

        // Raylib Camera functions
        Camera3D getCamera() const;
        void updateCamera();

        // Raylib window functions
        void init();
        void setTargetFPS(int fps);
        bool shouldClose();
        void beginDrawing();
        void clearBackground(Color color);
        void endDrawing();
        void close();

        // Raylib drawing functions
        void beginMode3D();
        void drawCube(Vector3 position, float width, float height, float length, Color color);
        void drawCubeWires(Vector3 position, float width, float height, float length, Color color);
        void drawGrid(int slices, float spacing);
        void endMode3D();

    private:
        int _width;
        int _height;
        std::string _title;
        GameCamera _camera;
};
