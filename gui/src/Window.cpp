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
    _camera = {
        { 0.0f, 10.0f, 10.0f }, // Camera position
        { 0.0f, 2.0f, 0.0f }, // Camera target
        { 0.0f, 1.0f, 0.0f }, // Camera up vector
        60.0f, // Camera FOV-Y
        CAMERA_PERSPECTIVE // Camera mode type
    };
    _cameraMode = CAMERA_FIRST_PERSON;
}

void Window::init()
{
    InitWindow(_width, _height, _title.c_str());
}

void Window::close()
{
    CloseWindow();
}

int Window::getScreenWidth()
{
    return GetScreenWidth();
}

int Window::getScreenHeight()
{
    return GetScreenHeight();
}

void Window::setTargetFPS(int fps)
{
    SetTargetFPS(fps);
}

void Window::disableCursor()
{
    DisableCursor();
}

bool Window::shouldClose()
{
    return WindowShouldClose();
}

void Window::beginDrawing()
{
    BeginDrawing();
}

void Window::endDrawing()
{
    EndDrawing();
}

void Window::clearBackground(Color color)
{
    ClearBackground(color);
}

Camera Window::getCamera() const
{
    return _camera;
}

int Window::getCameraMode() const
{
    return _cameraMode;
}

void Window::updateCamera()
{
    UpdateCamera(&_camera, _cameraMode);
}

void Window::setCameraPosition(Vector3 position)
{
    _camera.position = position;
}

void Window::setCameraTarget(Vector3 target)
{
    _camera.target = target;
}

void Window::setCameraUp(Vector3 up)
{
    _camera.up = up;
}

void Window::setCameraFovy(float fovy)
{
    _camera.fovy = fovy;
}

void Window::setCameraProjection(int projection)
{
    _camera.projection = projection;
}

void Window::setCameraMode(int mode)
{
    _cameraMode = mode;
}

void Window::parseCameraInputs()
{
    switch (GetKeyPressed()) {
        case KEY_ONE:
            printf("Camera mode: FREE\n");
            setCameraMode(CAMERA_FREE);
            setCameraUp({ 0.0f, 1.0f, 0.0f });
            break;
        case KEY_TWO:
            printf("Camera mode: FIRST PERSON\n");
            setCameraMode(CAMERA_FIRST_PERSON);
            setCameraUp({ 0.0f, 1.0f, 0.0f });
            break;
        case KEY_THREE:
            setCameraMode(CAMERA_THIRD_PERSON);
            setCameraUp({ 0.0f, 1.0f, 0.0f });
            break;
        case KEY_FOUR:
            setCameraMode(CAMERA_ORBITAL);
            setCameraUp({ 0.0f, 1.0f, 0.0f });
            break;
        default:
            break;
    }
}

void Window::beginMode3D()
{
    BeginMode3D(_camera);
}

void Window::endMode3D()
{
    EndMode3D();
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

void Window::drawPlane(Vector3 center, Vector2 size, Color color)
{
    DrawPlane(center, size, color);
}

bool Window::isKeyPressed(int key)
{
    return IsKeyPressed(key);
}
