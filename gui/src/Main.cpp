/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** main
*/

#include "Gui.hpp"
#include "Parser/ParseArguments.hpp"
#include "Socket.hpp"
#include "Window.hpp"
#include "Map.hpp"

int main(int argc, char *argv[])
{
    ParseArguments argsParser(argc, argv);

    /*
    ** Parse arguments
    */
    try {
        argsParser.parse();
        if (argsParser.getMachine().empty() || argsParser.getPort() <= 0 || argsParser.getPort() > 65535)
            throw std::runtime_error("Error: Invalid arguments");
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    /*
    ** Init socker and window, draw waiting screen while connecting
    */
    Socket socket(argsParser.getPort(), argsParser.getMachine());
    Window window(1280, 720, "Zappy GUI");
    window.init();

    if (!window.drawWaitingScreen(socket, argsParser.getMachine())) {
        window.close();
        return 84;
    }

    // Validate connection
    if (!argsParser.validateConnection(socket.receiveMessage())) {
        std::cerr << "Error: Connection failed" << std::endl;
        window.close();
        return 84;
    }

    int map_width = 10;
    int map_height = 10;

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

    window.disableCursor();
    while (!window.shouldClose())
    {
        window.parseCameraInputs();
        window.updateCamera();
        window.beginDrawing();
        window.clearBackground(RAYWHITE);

        window.beginMode3D();
        window.drawGrid(20, 10.0f);
        map.draw();
        window.endMode3D();

        window.drawText(TextFormat("X:%f Y:%f Z:%f", window.getCamera().position.x, window.getCamera().position.y, window.getCamera().position.z), 10, 40, 20, GRAY);
        if (selected)
            window.drawText("MODEL SELECTED", window.getScreenWidth() - 110, 10, 10, GREEN);
        window.drawFPS(10, 10);
        window.endDrawing();
    }
    map.unload();
    window.close();
    return 0;
}
