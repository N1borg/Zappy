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

void Window::log(int level, const std::string &msg, ...)
{
    va_list args;
    va_start(args, msg);
    TraceLog(level, msg.c_str(), args);
    va_end(args);
}

void Window::init()
{
    SetTargetFPS(144);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
    InitWindow(_width, _height, _title.c_str());
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

void Window::enableCursor()
{
    EnableCursor();
}

void Window::disableCursor()
{
    DisableCursor();
}

bool Window::isCursorHidden()
{
    return IsCursorHidden();
}

bool Window::isKeyPressed(int key)
{
    return IsKeyPressed(key);
}

bool Window::isKeyReleased(int key)
{
    return IsKeyReleased(key);
}

bool Window::isKeyDown(int key)
{
    return IsKeyDown(key);
}

bool Window::isKeyUp(int key)
{
    return IsKeyUp(key);
}

bool Window::isMouseButtonPressed(int button)
{
    return IsMouseButtonPressed(button);
}

bool Window::isMouseButtonReleased(int button)
{
    return IsMouseButtonReleased(button);
}

bool Window::isMouseButtonDown(int button)
{
    return IsMouseButtonDown(button);
}

bool Window::isMouseButtonUp(int button)
{
    return IsMouseButtonUp(button);
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

void Window::updateCamera()
{
    UpdateCamera(&_camera, getCameraMode());
}

void Window::parseCameraInputs()
{
    switch (GetKeyPressed()) {
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

void Window::drawCrosshair()
{

    int centerX = getScreenWidth() / 2;
    int centerY = getScreenHeight() / 2;
    int crosshairSize = 10; // Size of the crosshair lines
    int crosshairThickness = 2; // Thickness of the crosshair lines

    // Horizontal line
    DrawRectangle(centerX - crosshairSize, centerY - crosshairThickness / 2, 2 * crosshairSize, crosshairThickness, {0, 0, 0, 127});
    // Vertical line
    DrawRectangle(centerX - crosshairThickness / 2, centerY - crosshairSize, crosshairThickness, 2 * crosshairSize, {0, 0, 0, 127});
}

void Window::drawPlane(Vector3 position, Vector2 size, Color color)
{
    DrawPlane(position, size, color);
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
    int numDots = static_cast<int>(elapsedTime) % 4;
    std::string dots(numDots, '.');
    return string + dots;
}

void Window::drawConnection(bool isConnected, std::string ip, bool isReconnecting, int elapsedTime)
{
    Color color = isConnected ? GREEN : DARKGRAY;
    std::string connectStatus = isConnected ? "Connected to " : "Connecting to ";
    std::string connectDots = animateTextDots(connectStatus + ip, elapsedTime);
    std::string reconnecting = "Connection lost, reconnecting";

    beginDrawing();
    clearBackground(RAYWHITE);

    drawText(connectDots.c_str(), (getScreenWidth() - MeasureText((connectStatus + ip + "...").c_str(), 20)) / 2, (getScreenHeight() - 20) / 2, 20, color);

    // If reconnecting, display a message
    if (isReconnecting) {
        connectDots = animateTextDots(reconnecting, elapsedTime);
        drawText(connectDots.c_str(), (getScreenWidth() - MeasureText("Connection lost, reconnecting...", 20)) / 2, (getScreenHeight() - 20) / 2 + 40, 20, RED);
    }
    endDrawing();
}

int Window::drawWaitingScreen(Socket &socket, ParseArguments &argsParser, bool isReconnecting = false)
{
    std::thread connectionThread(&Socket::attemptConnection, &socket);
    std::string ip = argsParser.getMachine();
    float elapsedTime = 0.0f;

    // Wait for connection
    EnableCursor();
    while (!socket.isConnected()) {
        if (shouldClose()) {
            connectionThread.detach();
            return 0;
        }
        elapsedTime += GetFrameTime();
        drawConnection(false, ip, isReconnecting, elapsedTime);
    }
    connectionThread.join();
    drawConnection(true, ip, isReconnecting, elapsedTime);

    // Validate connection
    if (argsParser.validateConnection(socket.receiveMessage()))
        socket.sendMessage("GRAPHIC\n");
    else {
        std::cerr << "Error: Connection failed" << std::endl;
        close();
        return 0;
    }

    if (socket.isConnected())
        return 1;
    return 0;
}
