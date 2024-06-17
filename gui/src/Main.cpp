/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** main
*/

#include "Gui.hpp"
#include "Parser.hpp"
#include "Socket.hpp"
#include "Window.hpp"
#include "Map.hpp"

int waitConnection(Parser &parser, Socket &socket, Window &window)
{
    std::thread connectionThread(&Socket::attemptConnection, &socket);

    float elapsedTime = 0.0f;

    while (!socket.isConnected()) {
        if (window.shouldClose()) {
            connectionThread.detach();
            return 0;
        }
        elapsedTime += GetFrameTime();

        window.beginDrawing();
        window.clearBackground(RAYWHITE);

        std::string connectingText = window.animateTextDots("Connecting to " + parser.getMachine(), elapsedTime);
        window.drawText(connectingText.c_str(), (window.getScreenWidth() - MeasureText(("Connecting to " + parser.getMachine() + "...").c_str(), 20)) / 2, (window.getScreenHeight() - 20) / 2, 20, DARKGRAY);

        window.endDrawing();
    }

    connectionThread.join();

    if (socket.isConnected()) {
        return 1;
    } else {
        while (!window.shouldClose()) {
            window.beginDrawing();
            window.clearBackground(RAYWHITE);
            window.drawText("Failed to connect", (window.getScreenWidth() - MeasureText("Failed to connect", 20)) / 2, (window.getScreenHeight() - 20) / 2, 20, RED);
            window.endDrawing();
        }
    }
    return 0;
}

int main(int argc, char *argv[])
{
    Parser parser(argc, argv);

    try {
        parser.parseArguments();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    if (parser.getMachine().empty() || parser.getPort() <= 0 || parser.getPort() > 65535) {
        throw std::runtime_error("Error: Invalid arguments");
        return 84;
    }

    Socket socket(parser.getPort(), parser.getMachine());
    Window window(1280, 720, "Zappy GUI");
    window.init();

    if (!waitConnection(parser, socket, window)) {
        window.close();
        return 84;
    }

    int map_width = 10;
    int map_height = 10;

    window.setCameraPosition({(map_width / 2.0f) * 10.0f, 80.0f, (map_height / 2.0f) * 10.0f});
    window.setCameraTarget({0.0f, 10.0f, 0.0f});
    window.setCameraUp({0.0f, 1.0f, 0.0f});
    window.setCameraFovy(45.0f);
    window.setCameraProjection(CAMERA_PERSPECTIVE);

    Map map(map_width, map_height);
    std::vector<std::vector<Tile_t>> tiles = map.getTiles();

    bool selected = false;

    map.setPlayer(1, 3, true);
    map.setPlayer(1, 8, true);
    map.setPlayer(4, 8, true);
    map.setPlayer(5, 1, true);
    map.setFood(2, 3, true);
    map.setFood(1, 5, true);
    map.setFood(4, 2, true);
    map.setFood(5, 1, true);
    map.setEgg(4, 3, true);
    map.setEgg(3, 5, true);
    map.setLinemate(1, 1, true);
    map.setDeraumere(2, 2, true);
    map.setSibur(3, 3, true);
    map.setMendiane(4, 4, true);
    map.setPhiras(5, 5, true);
    map.setThystame(6, 6, true);

    while (!WindowShouldClose())
    {
        window.updateCamera();

        window.beginDrawing();
            window.clearBackground(RAYWHITE);

            window.beginMode3D();
                window.drawGrid(20, 10.0f);
                map.draw();
            window.endMode3D();

            window.drawText(TextFormat("X:%f Y:%f Z:%f", window.getCamera().position.x, window.getCamera().position.y, window.getCamera().position.z), 10, 40, 20, GRAY);
            if (selected)
                window.drawText("MODEL SELECTED", GetScreenWidth() - 110, 10, 10, GREEN);
            window.drawFPS(10, 10);
        window.endDrawing();
    }
    map.unload();
    CloseWindow();
    return 0;
}
