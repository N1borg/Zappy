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
        Window();
        Window(int width, int height, std::string title);
        ~Window();

        // Encapsulation of raylib functions
        void init() { InitWindow(_width, _height, _title.c_str()); }
        void setTargetFPS(int fps) { SetTargetFPS(fps); }
        bool shouldClose() { return WindowShouldClose(); }
        void beginDrawing() { BeginDrawing(); }
        void clearBackground(Color color) { ClearBackground(color); }
        void endDrawing() { EndDrawing(); }
        void close() { CloseWindow(); }

    private:
        int _width;
        int _height;
        std::string _title;
        // Camera3D _camera;
};