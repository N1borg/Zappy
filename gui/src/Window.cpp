/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Window
*/

#include "../include/Window.hpp"

Window::Window(int width, int height, std::string title)
{
    _width = width;
    _height = height;
    _title = title;
    // _camera = {0};
}

void Window::init()
{
    InitWindow(_width, _height, _title.c_str());
}

void Window::setTargetFPS(int fps)
{
    SetTargetFPS(fps);
}

bool Window::shouldClose()
{
    return WindowShouldClose();
}

void Window::beginDrawing()
{
    BeginDrawing();
}

void Window::clearBackground(Color color)
{
    ClearBackground(color);
}

void Window::endDrawing()
{
    EndDrawing();
}

void Window::close()
{
    CloseWindow();
}
