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
    _camera.position = {0.0f, 100.0f, 10.0f};
    _camera.target = {0.0f, 10.0f, 0.0f};
    _camera.up = {0.0f, 1.0f, 0.0f};
    _camera.fovy = 60.0f;
    _camera.projection = CAMERA_PERSPECTIVE;
    _cameraMode = CAMERA_FREE;
}

void Window::init()
{
    SetTargetFPS(60);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
    InitWindow(_width, _height, _title.c_str());
    DisableCursor();
}

void Window::close()
{
    CloseWindow();
}

bool Window::shouldClose()
{
    return WindowShouldClose();
}

void Window::setTargetFPS(int fps)
{
    SetTargetFPS(fps);
}

int Window::getScreenWidth() const
{
    return GetScreenWidth();
}

int Window::getScreenHeight() const
{
    return GetScreenHeight();
}

Camera3D Window::getCamera() const
{
    return _camera;
}

int Window::getCameraMode()
{
    return _cameraMode;
}

void Window::setCameraMode(int mode)
{
    _cameraMode = mode;
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

void Window::updateCamera()
{
    UpdateCamera(&_camera, getCameraMode());
}

void Window::parseCameraInput()
{
    switch (GetKeyPressed()) {
        case KEY_ONE:
            setCameraMode(CAMERA_FIRST_PERSON);
            setCameraUp({0.0f, 1.0f, 0.0f});
            break;
        case KEY_TWO:
            setCameraMode(CAMERA_THIRD_PERSON);
            setCameraUp({0.0f, 1.0f, 0.0f});
            break;
        case KEY_THREE:
            setCameraMode(CAMERA_FREE);
            setCameraUp({0.0f, 1.0f, 0.0f});
            break;
        case KEY_FOUR:
            setCameraMode(CAMERA_ORBITAL);
            setCameraUp({0.0f, 1.0f, 0.0f});
            break;
    }
}

void Window::beginDrawing()
{
    BeginDrawing();
}

void Window::endDrawing()
{
    EndDrawing();
}

void Window::beginMode3D()
{
    BeginMode3D(_camera);
}

void Window::endMode3D()
{
    EndMode3D();
}

void Window::clearBackground(Color color)
{
    ClearBackground(color);
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

std::string Window::animateTextDots(const std::string &string, float elapsedTime)
{
    int dots = static_cast<int>(floor(elapsedTime * 4.0f)) % 4;
    std::string dotsStr(dots, '.');
    return string + dotsStr;
}

int Window::drawWaitingScreen(Socket &socket, const std::string machine)
{
    std::thread connectionThread(&Socket::attemptConnection, &socket);

    float elapsedTime = 0.0f;

    while (!socket.isConnected()) {
        if (shouldClose()) {
            connectionThread.detach();
            return 0;
        }
        elapsedTime += GetFrameTime();

        beginDrawing();
        clearBackground(RAYWHITE);

        std::string connectingText = animateTextDots("Connecting to " + machine, elapsedTime);
        drawText(connectingText.c_str(), (getScreenWidth() - MeasureText(("Connecting to " + machine + "...").c_str(), 20)) / 2, (getScreenHeight() - 20) / 2, 20, DARKGRAY);

        endDrawing();
    }

    connectionThread.join();

    if (socket.isConnected())
        return 1;
    return 0;
}
