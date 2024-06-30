/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Window
*/

#pragma once

#include "Parser/ParseArguments.hpp"
#include "Socket.hpp"
#include "Map.hpp"

#include <raylib.h>
#include <math.h>
#include <string>

class Window {
public:
    Window(int width, int height, std::string title);
    ~Window() = default;

    // Raylib window functions
    void init();
    void close();
    bool shouldClose() const { return WindowShouldClose(); }
    void setTargetFPS(int fps) { SetTargetFPS(fps); }
    int getScreenWidth() const { return GetScreenWidth(); }
    int getScreenHeight() const { return GetScreenHeight(); }
    void enableCursor() { EnableCursor(); }
    void disableCursor() { DisableCursor(); }
    bool isCursorHidden() { return IsCursorHidden(); }
    bool isKeyPressed(int key) { return IsKeyPressed(key); }
    bool isKeyReleased(int key) { return IsKeyReleased(key); }
    bool isKeyDown(int key) { return IsKeyDown(key); }
    bool isKeyUp(int key) { return IsKeyUp(key); }
    bool isMouseButtonPressed(int button) { return IsMouseButtonPressed(button); }
    bool isMouseButtonReleased(int button) { return IsMouseButtonReleased(button); }
    bool isMouseButtonDown(int button) { return IsMouseButtonDown(button); }
    bool isMouseButtonUp(int button) { return IsMouseButtonUp(button); }
    void playMusic(const std::string &path);

    // Raylib Camera functions
    Camera3D getCamera() const { return _camera; }
    int getCameraMode() const { return _cameraMode; }
    void setCameraMode(int mode) { _cameraMode = mode; }
    void setCameraPosition(Vector3 position) { _camera.position = position; }
    void setCameraTarget(Vector3 target) { _camera.target = target; }
    void setCameraUp(Vector3 up) { _camera.up = up; }
    void setCameraFovy(float fovy) { _camera.fovy = fovy; }
    void setCameraProjection(int projection) { _camera.projection = projection; }
    void updateCamera() { UpdateCamera(&_camera, getCameraMode()); }
    void parseCameraInputs();

    // Raylib drawing functions
    void beginDrawing() { BeginDrawing(); }
    void endDrawing() { EndDrawing(); }
    void beginMode3D() { BeginMode3D(_camera); }
    void endMode3D() { EndMode3D(); }
    void clearBackground(Color color) { ClearBackground(color); }
    void drawCrosshair();
    void drawPlane(Vector3 position, Vector2 size, Color color) { DrawPlane(position, size, color); }
    void drawGrid(int slices, float spacing) { DrawGrid(slices, spacing); }
    void drawText(const char *text, int posX, int posY, int fontSize, Color color) { DrawText(text, posX, posY, fontSize, color); }
    void drawFPS(int posX, int posY) { DrawFPS(posX, posY); }
    void drawGeneralInfo(Map map);
    int drawTeamNames(Map map);
    void drawTileInfo(Tile_t tile);

    std::string animateTextDots(const std::string &string, float elapsedTime);
    int drawWaitingScreen(Socket &socket, std::string ip, bool isReconnecting);
    void drawConnection(bool isConnected, std::string ip, bool isReconnecting, int elapsedTime);

    void log(int level, const std::string &msg, ...);

private:
    int _width;
    int _height;
    std::string _title;
    Camera _camera;
    int _cameraMode;
    Music _music;
};
