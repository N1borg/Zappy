/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Window
*/

#pragma once

#include <raylib.h>
#include <math.h>
#include <string>

#include "Camera.hpp"

class Window {
public:
    Window(int width, int height, std::string title);
    ~Window() = default;

    // Raylib Camera functions
    Camera3D getCamera() const;
    void setCameraPosition(Vector3 position);
    void setCameraTarget(Vector3 target);
    void setCameraUp(Vector3 up);
    void setCameraFovy(float fovy);
    void setCameraProjection(int projection);
    void updateCamera();

    // Raylib window functions
    void init();
    void setTargetFPS(int fps);
    bool shouldClose();
    void close();
    void clearBackground(Color color);
    int getScreenWidth() const;
    int getScreenHeight() const;

    // Raylib drawing functions
    void beginDrawing();
    void endDrawing();
    void beginMode3D();
    void endMode3D();
    void drawCube(Vector3 position, float width, float height, float length, Color color);
    void drawCubeWires(Vector3 position, float width, float height, float length, Color color);
    void drawGrid(int slices, float spacing);
    void drawText(const char *text, int posX, int posY, int fontSize, Color color);
    void drawFPS(int posX, int posY);

    std::string animateTextDots(const std::string &string, float elapsedTime);

private:
    int _width;
    int _height;
    std::string _title;
    GameCamera _camera;
};
