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
        if (!socket.isConnected()) {
            RaylibWrapper::log(LOG_ERROR, "Connection lost");
            if (!game.getWindow()->waitingConnection(socket, parser.getMachine(), true))
                break;
        }

        elapsedTime += RaylibWrapper::getFrameTime();
        game.parseInputs();
        game.render(elapsedTime);
    }
    game.stop();
    return 0;

    // Map map(mapWidth, mapHeight, timeUnit, teams);
    // std::vector<std::vector<Tile_t>> tiles = map.getTiles();

    // window.setCameraPosition({0.0f, 20.0f, 0.0f});
    // window.setCameraTarget({(mapWidth / 2.0f) * 10.0f, 0.0f, (mapHeight / 2.0f) * 10.0f});

    // map.addPlayer(0, 0, 0, Orientation::North, 1, "team1");
    // map.addPlayer(1, 1, 1, Orientation::East, 1, "team2");
    // map.addPlayer(2, 2, 2, Orientation::South, 1, "team3");
    // map.addPlayer(3, 5, 3, Orientation::West, 1, "team4");
    // map.addPlayer(4, 4, 4, Orientation::North, 1, "team5");
    // map.addPlayer(5, 6, 5, Orientation::East, 1, "team6");
    // map.addPlayer(6, 2, 6, Orientation::South, 1, "team7");
    // map.addPlayer(7, 4, 7, Orientation::West, 1, "team8");
    // map.addEgg(0, 0, 0, 0, "team1");
    // map.addEgg(1, 0, 1, 1, "team2");
    // map.addEgg(2, 0, 2, 2, "team3");
    // map.addEgg(3, 0, 3, 3, "team4");
    // map.addEgg(4, 0, 4, 4, "team5");
    // map.addEgg(5, 0, 5, 5, "team6");
    // map.addEgg(6, 0, 6, 6, "team7");
    // map.addEgg(7, 0, 7, 7, "team8");
    // map.addFood(2, 3);
    // map.addFood(1, 5);
    // map.addFood(4, 2);
    // map.addFood(5, 1);
    // map.addLinemate(1, 1);
    // map.addDeraumere(2, 2);
    // map.addSibur(3, 3);
    // map.addMendiane(4, 4);
    // map.addPhiras(5, 5);
    // map.addThystame(6, 6);

    // map.addFood(0, 0);
    // map.addLinemate(0, 0);
    // map.addDeraumere(0, 0);
    // map.addSibur(0, 0);
    // map.addMendiane(0, 0);
    // map.addPhiras(0, 0);
    // map.addThystame(0, 0);

    // bool isTileSelected = false;
    // bool isFrequencySelected = false;

    // // Starts thread for reading messages
    // socket.startThread();

    // window.playMusic("gui/resources/game_music.mp3");
    // window.disableCursor();
    // while (!window.shouldClose()) {
    //     // Check socket disconnection
    //     if (!socket.isConnected()) {
    //         window.log(LOG_ERROR, "Connection lost");
    //         if (!window.drawWaitingScreen(socket, argsParser, true))
    //             break;
    //     }

    //     if (window.isMouseButtonPressed(MOUSE_LEFT_BUTTON))
    //         isTileSelected = map.selectTile(GetMouseRay({window.getScreenWidth() / 2.0f, window.getScreenHeight() / 2.0f}, window.getCamera()));
    //     if (window.isKeyPressed(KEY_ENTER))
    //         !isFrequencySelected;

    //     window.parseCameraInputs();
    //     window.updateCamera();
    //     window.beginDrawing();
    //         window.clearBackground(SKYBLUE);

    //         window.beginMode3D();
    //             map.draw();
    //             map.drawTransparent();
    //         window.endMode3D();

    //         window.drawCrosshair();
    //         window.drawGeneralInfo(map);
    //         window.drawFPS(10, window.getScreenHeight() - 30);
    //         if (isTileSelected)
    //             window.drawTileInfo(map.getSelectedTile());
    //     window.endDrawing();
    // }
    // map.unload();
    // window.close();
    // socket.stopThread();
    // return 0;
}
