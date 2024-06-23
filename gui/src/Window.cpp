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
    _camera = new CameraObject();
    _minimap = new CameraObject();

    _camera->setCameraPosition({0.0f, 10.0f, 10.0f});
    _camera->setCameraTarget({0.0f, 10.0f, 0.0f});
    _camera->setCameraUp({0.0f, 1.0f, 0.0f});
    _camera->setCameraFovy(60.0f);
    _camera->setCameraProjection(CAMERA_PERSPECTIVE);
    _camera->setCameraMode(CAMERA_FREE);
    playMusic("gui/resources/game_music.mp3");
}

void Window::init()
{
    RaylibWrapper::setTargetFPS(144);
    RaylibWrapper::setConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
    RaylibWrapper::initWindow(_width, _height, _title.c_str());
    RaylibWrapper::initAudioDevice();
}

void Window::close()
{
    RaylibWrapper::unloadMusicStream(_music);
    RaylibWrapper::closeAudioDevice();
    RaylibWrapper::closeWindow();
}

CameraObject *Window::getCamera()
{
    return _camera;
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
        RaylibWrapper::drawText(RaylibWrapper::textFormat("  %s: p(%d) e(%d)", team.getTeamName().c_str(), team.getNumberPlayers(), team.getNumberEggs()), 10, 140 + i * 20, 20, team.getTeamColor());
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
    std::thread connectionThread(&Socket::attemptConnection, &socket);
    RaylibWrapper::enableCursor();

    float elapsedTime = 0.0f;
    while (!socket.isConnected()) {
        if (RaylibWrapper::shouldClose()){
            connectionThread.detach();
            return 0;
        }
        elapsedTime += RaylibWrapper::getFrameTime();
        drawConnectionText(ip, isReconnecting, elapsedTime);
    }
    connectionThread.join();
    return 1;
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

void Window::playMusic(const char *path)
{
    _music = RaylibWrapper::loadMusicStream(path);
    RaylibWrapper::playMusicStream(_music);
    RaylibWrapper::setMusicVolume(_music, 0.1f);
}