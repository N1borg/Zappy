/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Window
*/

#include "Window.hpp"

Window::Window(int width, int height, std::string title)
{
    _width = width;
    _height = height;
    _title = title;
    _camera = GameCamera();
}

void Window::init()
{
    SetTargetFPS(60);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
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

void Window::setCameraPosition(Vector3 position)
{
    _camera.setPosition(position);
}

void Window::setCameraTarget(Vector3 target)
{
    _camera.setTarget(target);
}

void Window::setCameraUp(Vector3 up)
{
    _camera.setUp(up);
}

void Window::setCameraFovy(float fovy)
{
    _camera.setFovy(fovy);
}

void Window::setCameraProjection(int projection)
{
    _camera.setProjection(projection);
}

void Window::updateCamera()
{
    _camera.updateCamera();
}

int Window::getScreenWidth() const
{
    return GetScreenWidth();
}

int Window::getScreenHeight() const
{
    return GetScreenHeight();
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

void Window::drawText(const char *text, int posX, int posY, int fontSize, Color color)
{
    DrawText(text, posX, posY, fontSize, color);
}

void Window::drawFPS(int posX, int posY)
{
    DrawFPS(posX, posY);
}

void Window::endMode3D()
{
    EndMode3D();
}

std::string Window::animateTextDots(const std::string &string, float elapsedTime)
{
    int dots = static_cast<int>(floor(elapsedTime * 4.0f)) % 4;
    std::string dotsStr(dots, '.');
    return string + dotsStr;
}
