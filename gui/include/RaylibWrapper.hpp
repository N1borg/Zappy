/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** RaylibWrapper
*/

#ifndef RAYLIBWRAPPER_HPP_
#define RAYLIBWRAPPER_HPP_

#include <raylib.h>

class RaylibWrapper {
    public:
        // Window handling functions
        static void initWindow(int width, int height, const char *title) { InitWindow(width, height, title); }
        static void closeWindow() { CloseWindow(); }
        static bool shouldClose() { return WindowShouldClose(); }
        static void setTargetFPS(int fps) { SetTargetFPS(fps); }
        static int getScreenWidth() { return GetScreenWidth(); }
        static int getScreenHeight() { return GetScreenHeight(); }
        static void enableCursor() { EnableCursor(); }
        static void disableCursor() { DisableCursor(); }
        static bool isCursorHidden() { return IsCursorHidden(); }

        // Input handling functions
        static int getKeyPressed() { return GetKeyPressed(); }
        static bool isKeyPressed(int key) { return IsKeyPressed(key); }
        static bool isKeyReleased(int key) { return IsKeyReleased(key); }
        static bool isKeyDown(int key) { return IsKeyDown(key); }
        static bool isKeyUp(int key) { return IsKeyUp(key); }
        static bool isMouseButtonPressed(int button) { return IsMouseButtonPressed(button); }
        static bool isMouseButtonReleased(int button) { return IsMouseButtonReleased(button); }
        static bool isMouseButtonDown(int button) { return IsMouseButtonDown(button); }
        static bool isMouseButtonUp(int button) { return IsMouseButtonUp(button); }

        // Drawing functions
        static void beginDrawing() { BeginDrawing(); }
        static void endDrawing() { EndDrawing(); }
        static void beginMode3D(Camera3D camera) { BeginMode3D(camera); }
        static void endMode3D() { EndMode3D(); }
        static void clearBackground(Color color) { ClearBackground(color); }
        static void drawFPS(int posX, int posY) { DrawFPS(posX, posY); }
        static void drawText(const char *text, int posX, int posY, int fontSize, Color color) { DrawText(text, posX, posY, fontSize, color); }
        static void drawRectangle(int posX, int posY, int width, int height, Color color) { DrawRectangle(posX, posY, width, height, color); }
        static void drawPlane(Vector3 position, Vector2 size, Color color) { DrawPlane(position, size, color); }
        static void drawGrid(int slices, float spacing) { DrawGrid(slices, spacing); }

        // Camera functions
        static void updateCamera(Camera3D *camera, int mode) { UpdateCamera(camera, mode); }

        // Other
        static float getFrameTime() { return GetFrameTime(); }
        static int measureText(const char *text, int fontSize) { return MeasureText(text, fontSize); }
        static void log(int level, const char *msg, ...) { va_list args; va_start(args, msg); TraceLog(level, msg, args); va_end(args); }
        static void setConfigFlags(unsigned int flags) { SetConfigFlags(flags); }
};

#endif /* !RAYLIBWRAPPER_HPP_ */
