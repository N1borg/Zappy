/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Window
*/

#pragma once

#include "raylib.h"
#include <string>

class Window {
    public:
        Window() = default;
        Window(int width, int height, std::string title);
        ~Window() = default;

        // Raylib functions
        void init();
        void setTargetFPS(int fps);
        bool shouldClose();
        void beginDrawing();
        void clearBackground(Color color);
        void endDrawing();
        void close();

    private:
        int _width;
        int _height;
        std::string _title;
        // Camera3D _camera;
};