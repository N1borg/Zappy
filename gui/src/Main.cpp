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

    if (!window.drawWaitingScreen(socket, argsParser, false))
        return 84;

    socket.sendMessage("msz\n");
    std::istringstream msg = std::istringstream(socket.receiveMessage());
    std::string mapSz, mapWidthStr, mapHeightStr;
    int mapWidth, mapHeight;

    try {
        msg >> mapSz >> mapWidthStr >> mapHeightStr;
        mapWidth = std::stoi(mapWidthStr);
        mapHeight = std::stoi(mapHeightStr);
    } catch (const std::exception &e) {
        window.log(LOG_ERROR, "INIT: Invalid map size");
        window.close();
        return 84;
    }

    // Create map
    Team team1("team1");
    team1.setTeamColor(RED);
    Team team2("team2");
    team2.setTeamColor(GREEN);
    Team team3("team3");
    team3.setTeamColor(BLUE);

    Map map(mapWidth, mapHeight);
    std::vector<std::vector<Tile_t>> tiles = map.getTiles();

    window.setCameraPosition({0.0f, 20.0f, 0.0f});
    window.setCameraTarget({(mapWidth / 2.0f) * 10.0f, 0.0f, (mapHeight / 2.0f) * 10.0f});

    Model playerModel = LoadModel("gui/resources/player.glb");
    Model eggModel = LoadModel("gui/resources/egg.glb");

    Player player1(playerModel, team1);
    Player player2(playerModel, team2);
    Egg egg1(eggModel, team1);
    Egg egg2(eggModel, team2);
    map.setPlayer(1, 3, player1);
    map.setFood(2, 3, true);
    map.setFood(1, 5, true);
    map.setFood(4, 2, true);
    map.setFood(5, 1, true);
    map.setEgg(4, 3, egg1);
    map.setEgg(3, 5, egg2);
    map.setLinemate(1, 1, true);
    map.setDeraumere(2, 2, true);
    map.setSibur(3, 3, true);
    map.setMendiane(4, 4, true);
    map.setPhiras(5, 5, true);
    map.setThystame(6, 6, true);

    map.setPlayer(0, 0, player2);
    map.setEgg(0, 0, egg1);
    map.setFood(0, 0, true);
    map.setLinemate(0, 0, true);
    map.setDeraumere(0, 0, true);
    map.setSibur(0, 0, true);
    map.setMendiane(0, 0, true);
    map.setPhiras(0, 0, true);
    map.setThystame(0, 0, true);

    // Starts thread for reading messages
    socket.startThread();

    window.disableCursor();
    while (!window.shouldClose()) {
        // Check socket disconnection
        if (!socket.isConnected()) {
            window.log(LOG_ERROR, "Connection lost");
            if (!window.drawWaitingScreen(socket, argsParser, true))
                break;
        }

        if (window.isMouseButtonPressed(MOUSE_LEFT_BUTTON) || window.isKeyPressed(KEY_ENTER))
            map.selectTile(GetMouseRay({window.getScreenWidth() / 2.0f, window.getScreenHeight() / 2.0f}, window.getCamera()));

        window.parseCameraInputs();
        window.updateCamera();
        window.beginDrawing();
        window.clearBackground(SKYBLUE);

        window.beginMode3D();
        window.drawGrid(20, 10.0f);
        map.draw();
        map.drawTransparent();
        window.endMode3D();

        window.drawText(TextFormat("X:%f Y:%f Z:%f", window.getCamera().position.x, window.getCamera().position.y, window.getCamera().position.z), 10, 40, 20, GRAY);

        window.drawText(TextFormat("Map size: (%d, %d)", map.getWidth(), map.getHeight()), 10, 60, 20, GRAY);

        window.drawCrosshair();
        window.drawFPS(10, 10);
        window.endDrawing();
    }
    map.unload();
    window.close();
    socket.stopThread();
    return 0;
}
