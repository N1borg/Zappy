/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** main
*/

#include "Game/Game.hpp"
#include "Orientation.hpp"

int main(int argc, char *argv[])
{
    // Parse arguments
    ParseArguments parser(argc, argv);
    try {
        parser.parse();
        if (parser.getMachine().empty() || parser.getPort() <= 0 || parser.getPort() > 65535)
            throw std::runtime_error("Error: Invalid arguments");
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    // Init game
    Socket socket(parser.getPort(), parser.getMachine());
    Game game(&socket);
    game.init();

    float elapsedTime = 0.0f;
    while (!RaylibWrapper::shouldClose()) {
        // if (!socket.isConnected()) {
        //     RaylibWrapper::log(LOG_ERROR, "Connection lost");
        //     if (!game.getWindow()->waitingConnection(socket, parser.getMachine(), true))
        //         break;
        // }

        elapsedTime += RaylibWrapper::getFrameTime();
        game.parseInputs();
        game.render(elapsedTime);
    }
    game.stop();
    return 0;

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
    std::vector<Team> teams;
    Team team1("team1");
    team1.setTeamColor(RED);
    teams.push_back(team1);
    Team team2("team2");
    team2.setTeamColor(YELLOW);
    teams.push_back(team2);
    Team team3("team3");
    team3.setTeamColor(BLUE);
    teams.push_back(team3);

    Map map(mapWidth, mapHeight, timeUnit, teams);
    std::vector<std::vector<Tile_t>> tiles = map.getTiles();

    window.setCameraPosition({0.0f, 20.0f, 0.0f});
    window.setCameraTarget({(mapWidth / 2.0f) * 10.0f, 0.0f, (mapHeight / 2.0f) * 10.0f});

    map.addPlayer(0, 0, 0, Orientation::North, 1, "team1");
    map.addPlayer(1, 1, 1, Orientation::East, 1, "team2");
    map.addPlayer(2, 2, 2, Orientation::South, 1, "team3");
    map.addEgg(0, 0, 0, 0, "team1");
    map.addEgg(1, 0, 1, 1, "team2");
    map.addEgg(2, 0, 2, 2, "team3");
    map.addFood(2, 3);
    map.addFood(1, 5);
    map.addFood(4, 2);
    map.addFood(5, 1);
    map.addLinemate(1, 1);
    map.addDeraumere(2, 2);
    map.addSibur(3, 3);
    map.addMendiane(4, 4);
    map.addPhiras(5, 5);
    map.addThystame(6, 6);

    map.addFood(0, 0);
    map.addLinemate(0, 0);
    map.addDeraumere(0, 0);
    map.addSibur(0, 0);
    map.addMendiane(0, 0);
    map.addPhiras(0, 0);
    map.addThystame(0, 0);

    bool isTileSelected = false;
    bool isFrequencySelected = false;

    // Starts thread for reading messages
    socket.startThread();

    window.playMusic("gui/resources/game_music.mp3");
    window.disableCursor();
    while (!window.shouldClose()) {
        // Check socket disconnection
        if (!socket.isConnected()) {
            window.log(LOG_ERROR, "Connection lost");
            if (!window.drawWaitingScreen(socket, argsParser, true))
                break;
        }

        if (window.isMouseButtonPressed(MOUSE_LEFT_BUTTON))
            isTileSelected = map.selectTile(GetMouseRay({window.getScreenWidth() / 2.0f, window.getScreenHeight() / 2.0f}, window.getCamera()));
        if (window.isKeyPressed(KEY_ENTER))
            !isFrequencySelected;

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
