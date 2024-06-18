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

class Window {
public:
    Window(int width, int height, std::string title);
    ~Window() = default;

    // Raylib window functions
    void init();
    void close();
    bool shouldClose();
    void setTargetFPS(int fps);
    int getScreenWidth() const;
    int getScreenHeight() const;

    // Raylib Camera functions
    Camera3D getCamera() const;
    int getCameraMode();
    void setCameraMode(int mode);
    void setCameraPosition(Vector3 position);
    void setCameraTarget(Vector3 target);
    void setCameraUp(Vector3 up);
    void setCameraFovy(float fovy);
    void setCameraProjection(int projection);
    void updateCamera();
    void parseCameraInput();

    // Raylib drawing functions
    void beginDrawing();
    void endDrawing();
    void beginMode3D();
    void endMode3D();
    void clearBackground(Color color);
    void drawGrid(int slices, float spacing);
    void drawText(const char *text, int posX, int posY, int fontSize, Color color);
    void drawFPS(int posX, int posY);

    std::string animateTextDots(const std::string &string, float elapsedTime);

private:
    int _width;
    int _height;
    std::string _title;
    Camera _camera;
    int _cameraMode;
};
