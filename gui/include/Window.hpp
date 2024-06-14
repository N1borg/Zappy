/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Window
*/

#pragma once

#include <raylib.h>
#include <string>

class Window {
    public:
        Window() = default;
        Window(int width, int height, std::string title);
        ~Window() = default;

        // Raylib Camera functions
        Camera getCamera() const;
        int getCameraMode() const;
        void updateCamera();
        void setCameraPosition(Vector3 position);
        void setCameraTarget(Vector3 target);
        void setCameraUp(Vector3 up);
        void setCameraFovy(float fovy);
        void setCameraProjection(int projection);
        void setCameraMode(int mode);
        void parseCameraInputs();

        // Raylib window functions
        void init();
        void close();
        bool shouldClose();
        void beginDrawing();
        void endDrawing();
        void setTargetFPS(int fps);
        void disableCursor();
        void clearBackground(Color color);
        int getScreenWidth();
        int getScreenHeight();
        bool isKeyPressed(int key);

        // Raylib drawing functions
        void beginMode3D();
        void drawCube(Vector3 position, float width, float height, float length, Color color);
        void drawCubeWires(Vector3 position, float width, float height, float length, Color color);
        void drawGrid(int slices, float spacing);
        void drawPlane(Vector3 center, Vector2 size, Color color);
        void endMode3D();

    private:
        int _width;
        int _height;
        std::string _title;
        Camera _camera;
        int _cameraMode;
};
