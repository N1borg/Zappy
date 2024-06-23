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
    setCameraPosition({0.0f, 10.0f, 10.0f});
    setCameraTarget({0.0f, 10.0f, 0.0f});
    setCameraUp({0.0f, 1.0f, 0.0f});
    setCameraFovy(60.0f);
    setCameraProjection(CAMERA_PERSPECTIVE);
    setCameraMode(CAMERA_FREE);
}

void Window::init()
{
    RaylibWrapper::setTargetFPS(144);
    RaylibWrapper::setConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
    RaylibWrapper::initWindow(_width, _height, _title.c_str());
}


Camera3D Window::getCamera() const
{
    return _camera;
}

int Window::getCameraMode() const
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

void Window::parseCameraInputs()
{
    switch (RaylibWrapper::getKeyPressed()) {
        case KEY_ONE:
            setCameraMode(CAMERA_FIRST_PERSON);
            setCameraUp({ 0.0f, 1.0f, 0.0f });
            break;
        case KEY_TWO:
            setCameraMode(CAMERA_THIRD_PERSON);
            setCameraUp({ 0.0f, 1.0f, 0.0f });
            break;
        case KEY_THREE:
            setCameraMode(CAMERA_FREE);
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

void Window::drawCrosshair()
{

    int centerX = RaylibWrapper::getScreenWidth() / 2;
    int centerY = RaylibWrapper::getScreenHeight() / 2;
    int crosshairSize = 10;
    int crosshairThickness = 2;

    RaylibWrapper::drawRectangle(centerX - crosshairSize, centerY - crosshairThickness / 2, 2 * crosshairSize, crosshairThickness, {0, 0, 0, 127});
    RaylibWrapper::drawRectangle(centerX - crosshairThickness / 2, centerY - crosshairSize, crosshairThickness, 2 * crosshairSize, {0, 0, 0, 127});
}

std::string Window::animateTextDots(const std::string &string, float elapsedTime)
{
    int numDots = static_cast<int>(elapsedTime) % 4;
    std::string dots(numDots, '.');
    return string + dots;
}

void Window::drawConnectionText(std::string ip, bool isReconnecting, int elapsedTime)
{
    std::string connectStatus = "Connecting to " + ip;
    std::string displayText = isReconnecting ? "Connection lost to " + ip : connectStatus;
    std::string animatedText = animateTextDots(displayText, elapsedTime);
    Color displayColor = isReconnecting ? RED : DARKGRAY;

    RaylibWrapper::beginDrawing();
    RaylibWrapper::clearBackground(RAYWHITE);

    int textWidth = RaylibWrapper::measureText(animatedText.c_str(), 20);
    RaylibWrapper::drawText(animatedText.c_str(), (RaylibWrapper::getScreenWidth() - textWidth) / 2, (RaylibWrapper::getScreenHeight() - 20) / 2, 20, displayColor);
    RaylibWrapper::endDrawing();
}

int Window::waitingConnection(Socket &socket, std::string ip, bool isReconnecting = false)
{
    std::thread connectionThread;
    if (!connectionThread.joinable())
        connectionThread = std::thread(&Socket::attemptConnection, &socket);

    float elapsedTime = 0.0f;
    while (!socket.isConnected() && !RaylibWrapper::shouldClose()) {
        elapsedTime += RaylibWrapper::getFrameTime();
        drawConnectionText(ip, isReconnecting, elapsedTime);
    }

    connectionThread.join();
    if (socket.isConnected())
        return 1;
    return 0;
}

void Window::waitingScreen(float elapsedTime)
{
    RaylibWrapper::beginDrawing();
    RaylibWrapper::clearBackground(RAYWHITE);

    std::string animatedTxt = animateTextDots("Waiting to server", elapsedTime);
    int textWidth = RaylibWrapper::measureText(animatedTxt.c_str(), 20);
    RaylibWrapper::drawText(animatedTxt.c_str(), (RaylibWrapper::getScreenWidth() - textWidth) / 2, RaylibWrapper::getScreenHeight() / 2, 20, GREEN);
    RaylibWrapper::endDrawing();
}
