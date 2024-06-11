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
    _camera = GameCamera();
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

Camera3D Window::getCamera() const
{
    return _camera.getCamera();
}

void Window::updateCamera()
{
    _camera.updateCamera();
}

void Window::beginMode3D()
{
    BeginMode3D(_camera.getCamera());
}

void Window::drawCube(Vector3 position, float width, float height, float length, Color color)
{
    DrawCube(position, width, height, length, color);
}

void Window::drawCubeWires(Vector3 position, float width, float height, float length, Color color)
{
    DrawCubeWires(position, width, height, length, color);
}

void Window::drawGrid(int slices, float spacing)
{
    DrawGrid(slices, spacing);
}

void Window::endMode3D()
{
    EndMode3D();
}
