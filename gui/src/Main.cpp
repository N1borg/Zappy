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
    std::vector<Team> teams;
    Team team1("team1");
    teams.push_back(team1);
    Team team2("team2");
    teams.push_back(team2);
    Team team3("team3");
    teams.push_back(team3);
    Team team4("team4");
    teams.push_back(team4);
    Team team5("team5");
    teams.push_back(team5);
    Team team6("team6");
    teams.push_back(team6);
    Team team7("team7");
    teams.push_back(team7);
    Team team8("team8");
    teams.push_back(team8);

    Map map(mapWidth, mapHeight, timeUnit, teams);
    std::vector<std::vector<Tile_t>> tiles = map.getTiles();

    window.setCameraPosition({0.0f, 20.0f, 0.0f});
    window.setCameraTarget({(mapWidth / 2.0f) * 10.0f, 0.0f, (mapHeight / 2.0f) * 10.0f});

    // Generate resources
    for (int i = 0; i < mapWidth; i++) {
        for (int j = 0; j < mapHeight; j++) {
            int randomResource = rand() % 6; // Generate a random resource type
            switch (randomResource) {
                case 0:
                    map.addFood(i, j);
                    break;
                case 1:
                    map.addLinemate(i, j);
                    break;
                case 2:
                    map.addDeraumere(i, j);
                    break;
                case 3:
                    map.addSibur(i, j);
                    break;
                case 4:
                    map.addMendiane(i, j);
                    break;
                case 5:
                    map.addPhiras(i, j);
                    break;
                case 6:
                    map.addThystame(i, j);
                    break;
                default:
                    break;
            }
        }
    }

    // Generate players
    for (std::size_t i = 0; i < map.getTeams().size(); i++) {
        int randomX = rand() % mapWidth;
        int randomY = rand() % mapHeight;
        int randomOrientation = rand() % 4;
        std::string teamName = "team" + std::to_string(i + 1);
        map.addPlayer(i, randomX, randomY, static_cast<Orientation>(randomOrientation), 1, teamName);
    }

    // Generate eggs
    for (std::size_t i = 0; i < map.getTeams().size() * 2; i++) {
        int randomX = rand() % mapWidth;
        int randomY = rand() % mapHeight;
        int randomTeam = rand() % map.getTeams().size();
        std::string teamName = "team" + std::to_string(randomTeam + 1);
        map.addEgg(i, randomX, randomY, randomTeam, teamName);
    }

    if (mapWidth > 1 || mapHeight > 1) {
        map.addFood(0, 0);
        map.addFood(0, 0);
        map.addLinemate(0, 0);
        map.addLinemate(0, 0);
        map.addLinemate(0, 0);
        map.addDeraumere(0, 0);
        map.addSibur(0, 0);
        map.addMendiane(0, 0);
        map.addPhiras(0, 0);
        map.addThystame(0, 0);
    }

    bool isTileSelected = false;

    // Starts thread for reading messages
    // Creates pointer
    std::shared_ptr<Map> mapPtr = std::make_shared<Map>(map);
    socket.startThread(mapPtr);

    window.playMusic("gui/resources/game_music.mp3");
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
                map.draw();
                map.drawTransparent();
            window.endMode3D();

            window.drawCrosshair();
            window.drawGeneralInfo(map);
            window.drawFPS(10, window.getScreenHeight() - 30);
            if (isTileSelected)
                window.drawTileInfo(map.getSelectedTile());
        window.endDrawing();
    }
    map.unload();
    window.close();
    socket.stopThread();
    return 0;
}
