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
    SetTargetFPS(144);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
    InitWindow(_width, _height, _title.c_str());
    InitAudioDevice();
}

void Window::close()
{
    UnloadMusicStream(_music);
    CloseAudioDevice();
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

void Window::playMusic(const std::string &path)
{
    _music = LoadMusicStream(path.c_str());
    _music.looping = true;
    PlayMusicStream(_music);
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

void Window::drawGeneralInfo(Map map)
{
    DrawRectangleRounded({2.0f, 2.0f, 250, 312.0f + map.getNbTeams() * 20.0f}, 0.1, 10, {255, 255, 255, 150});
    DrawRectangleRoundedLines({2.0f, 2.0f, 250, 312.0f + map.getNbTeams() * 20.0f}, 0.1, 10, BLACK);
    DrawText(TextFormat("X:%.2f Y:%.2f Z:%.2f", _camera.position.x, _camera.position.y, _camera.position.z), 10, 10, 20, GRAY);
    DrawText(TextFormat("Map size: (%d, %d)", map.getWidth(), map.getHeight()), 10, 30, 20, GRAY);
    DrawText(TextFormat("Frequency: %d", map.getFrequency()), 10, 50, 20, GRAY);
    DrawText(TextFormat("Camera mode: %d", getCameraMode()), 10, 70, 20, GRAY);
    DrawText(TextFormat("Is Game running: %d", map.isGameRunning()), 10, 90, 20, GRAY);
    DrawText(TextFormat("Teams (%d):", map.getNbTeams()), 10, 110, 20, GRAY);
    int i = drawTeamNames(map);
    DrawText(TextFormat("Players: %d", map.getNbPlayers()), 10, 130 + i * 20, 20, GRAY);
    DrawText(TextFormat("Eggs: %d", map.getNbEggs()), 10, 150 + i * 20, 20, GRAY);
    DrawText(TextFormat("Food: %d", map.getNbFood()), 10, 170 + i * 20, 20, GRAY);
    DrawText(TextFormat("Linemate: %d", map.getNbLinemate()), 10, 190 + i * 20, 20, GRAY);
    DrawText(TextFormat("Deraumere: %d", map.getNbDeraumere()), 10, 210 + i * 20, 20, GRAY);
    DrawText(TextFormat("Sibur: %d", map.getNbSibur()), 10, 230 + i * 20, 20, GRAY);
    DrawText(TextFormat("Mendiane: %d", map.getNbMendiane()), 10, 250 + i * 20, 20, GRAY);
    DrawText(TextFormat("Phiras: %d", map.getNbPhiras()), 10, 270 + i * 20, 20, GRAY);
    DrawText(TextFormat("Thystame: %d", map.getNbThystame()), 10, 290 + i * 20, 20, GRAY);
}

int Window::drawTeamNames(Map map)
{
    int i = 0;
    for (auto &team : map.getTeams()) {
        DrawText(TextFormat("  %s: p(%d) e(%d)", team.getTeamName().c_str(), team.getNumberPlayers(), team.getNumberEggs()), 10, 130 + i * 20, 20, team.getTeamColor());
        i++;
    }
    return i;
}

void Window::drawTileInfo(Tile_t tile)
{
    DrawRectangleRounded({getScreenWidth() - 152.0f, 2.0f, 150.0f, 212.0f}, 0.1, 10, {255, 255, 255, 150});
    DrawRectangleRoundedLines({getScreenWidth() - 152.0f, 2.0f, 150.0f, 212.0f}, 0.1, 10, BLACK);
    DrawText(TextFormat("Tile (%d, %d)", tile.xPos, tile.yPos), getScreenWidth() - MeasureText(TextFormat("Tile (%d, %d)", tile.xPos, tile.yPos), 20) - 10, 10, 20, GRAY);
    DrawText(TextFormat("Players: %d", tile.players.size()), getScreenWidth() - MeasureText(TextFormat("Players: %d", tile.players.size()), 20) - 10, 30, 20, GRAY);
    DrawText(TextFormat("Eggs: %d", tile.eggs.size()), getScreenWidth() - MeasureText(TextFormat("Eggs: %d", tile.eggs.size()), 20) - 10, 50, 20, GRAY);
    DrawText(TextFormat("Food: %d", tile.food.second), getScreenWidth() - MeasureText(TextFormat("Food: %d", tile.food.second), 20) - 10, 70, 20, GRAY);
    DrawText(TextFormat("Linemate: %d", tile.linemate.second), getScreenWidth() - MeasureText(TextFormat("Linemate: %d", tile.linemate.second), 20) - 10, 90, 20, GRAY);
    DrawText(TextFormat("Deraumere: %d", tile.deraumere.second), getScreenWidth() - MeasureText(TextFormat("Deraumere: %d", tile.deraumere.second), 20) - 10, 110, 20, GRAY);
    DrawText(TextFormat("Sibur: %d", tile.sibur.second), getScreenWidth() - MeasureText(TextFormat("Sibur: %d", tile.sibur.second), 20) - 10, 130, 20, GRAY);
    DrawText(TextFormat("Mendiane: %d", tile.mendiane.second), getScreenWidth() - MeasureText(TextFormat("Mendiane: %d", tile.mendiane.second), 20) - 10, 150, 20, GRAY);
    DrawText(TextFormat("Phiras: %d", tile.phiras.second), getScreenWidth() - MeasureText(TextFormat("Phiras: %d", tile.phiras.second), 20) - 10, 170, 20, GRAY);
    DrawText(TextFormat("Thystame: %d", tile.thystame.second), getScreenWidth() - MeasureText(TextFormat("Thystame: %d", tile.thystame.second), 20) - 10, 190, 20, GRAY);
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

void Window::log(int level, const std::string &msg, ...)
{
    va_list args;
    va_start(args, msg);
    TraceLog(level, msg.c_str(), args);
    va_end(args);
}
