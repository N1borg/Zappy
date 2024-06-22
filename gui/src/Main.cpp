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
#include "Orientation.hpp"

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

    socket.sendMessage("sgt\n");
    msg = std::istringstream(socket.receiveMessage());
    std::string timeUnitReq, timeUnitStr;
    int timeUnit;

    try {
        msg >> timeUnitReq >> timeUnitStr;
        timeUnit = std::stoi(timeUnitStr);
    } catch (const std::exception &e) {
        window.log(LOG_ERROR, "INIT: Invalid frequence");
        window.close();
        return 84;
    }

    // Create map
    Team team1("team1");
    team1.setTeamColor(RED);
    Team team2("team2");
    team2.setTeamColor(YELLOW);
    Team team3("team3");
    team3.setTeamColor(BLUE);

    Map map(mapWidth, mapHeight, timeUnit);
    std::vector<std::vector<Tile_t>> tiles = map.getTiles();

    window.setCameraPosition({0.0f, 20.0f, 0.0f});
    window.setCameraTarget({(mapWidth / 2.0f) * 10.0f, 0.0f, (mapHeight / 2.0f) * 10.0f});

    Model playerModel = LoadModel("gui/resources/player.glb");
    Model eggModel = LoadModel("gui/resources/egg.glb");

    Player player1(playerModel, 0, 1, 3, (Orientation) 0, team1);
    Player player2(playerModel, 1, 0, 0, (Orientation) 1, team2);
    Egg egg1(eggModel, 0, 0, 0, 0, team1);
    Egg egg2(eggModel, 1, 2, 4, 5, team3);
    map.addPlayer(1, 3, player1);
    map.addFood(2, 3);
    map.addFood(1, 5);
    map.addFood(4, 2);
    map.addFood(5, 1);
    map.addEgg(4, 3, egg1);
    map.addEgg(3, 5, egg2);
    map.addLinemate(1, 1);
    map.addDeraumere(2, 2);
    map.addSibur(3, 3);
    map.addMendiane(4, 4);
    map.addPhiras(5, 5);
    map.addThystame(6, 6);

    map.addPlayer(0, 0, player2);
    map.addEgg(0, 0, egg1);
    map.addFood(0, 0);
    map.addLinemate(0, 0);
    map.addDeraumere(0, 0);
    map.addSibur(0, 0);
    map.addMendiane(0, 0);
    map.addPhiras(0, 0);
    map.addThystame(0, 0);

    bool isTileSelected = false;

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
            isTileSelected = map.selectTile(GetMouseRay({window.getScreenWidth() / 2.0f, window.getScreenHeight() / 2.0f}, window.getCamera()));

        window.parseCameraInputs();
        window.updateCamera();
        window.beginDrawing();
            window.clearBackground(SKYBLUE);

            window.beginMode3D();
                window.drawGrid(20, 10.0f);
                map.draw();
                map.drawTransparent();
            window.endMode3D();

            window.drawCrosshair();
            window.drawFPS(10, 2);
            window.drawGeneralInfo(map);
            if (isTileSelected)
                window.drawTileInfo(map.getSelectedTile());
        window.endDrawing();
    }
    map.unload();
    window.close();
    socket.stopThread();
    return 0;
}
