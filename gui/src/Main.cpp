/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** main
*/

#include "Game.hpp"

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

    // // // Create map
    // // Map map(mapWidth, mapHeight);
    // // std::vector<std::vector<Tile_t>> tiles = map.getTiles();

    // // window.setCameraPosition({(mapWidth / 2.0f) * 10.0f, 20, (mapHeight / 2.0f) * 10.0f});

    // // map.setPlayer(1, 3, true);
    // // map.setPlayer(1, 8, true);
    // // map.setPlayer(4, 8, true);
    // // map.setPlayer(5, 1, true);
    // // map.setFood(2, 3, true);
    // // map.setFood(1, 5, true);
    // // map.setFood(4, 2, true);
    // // map.setFood(5, 1, true);
    // // map.setEgg(4, 3, true);
    // // map.setEgg(3, 5, true);
    // // map.setLinemate(1, 1, true);
    // // map.setDeraumere(2, 2, true);
    // // map.setSibur(3, 3, true);
    // // map.setMendiane(4, 4, true);
    // // map.setPhiras(5, 5, true);
    // // map.setThystame(6, 6, true);

    float elapsedTime = 0.0f;
    while (!RaylibWrapper::shouldClose()) {
        if (!socket.isConnected()) {
            RaylibWrapper::log(LOG_ERROR, "Connection lost");
            if (!game.getWindow()->waitingConnection(socket, parser.getMachine(), true))
                break;
        }

        game.render(elapsedTime);
        elapsedTime += RaylibWrapper::getFrameTime();

    //     // if (window.isMouseButtonPressed(MOUSE_LEFT_BUTTON) || window.isKeyPressed(KEY_ENTER))
    //     //     map.selectTile(GetMouseRay({window.getScreenWidth() / 2.0f, window.getScreenHeight() / 2.0f}, window.getCamera()));

    //     // window.parseCameraInputs();
    //     // window.updateCamera();
    //     // window.beginDrawing();
    //     // window.clearBackground(SKYBLUE);

    //     // window.beginMode3D();
    //     // window.drawGrid(20, 10.0f);
    //     // map.draw();
    //     // map.drawTransparent();
    //     // window.endMode3D();

    //     // window.drawText(TextFormat("X:%f Y:%f Z:%f", window.getCamera().position.x, window.getCamera().position.y, window.getCamera().position.z), 10, 40, 20, GRAY);

    //     // window.drawCrosshair();
    //     // window.drawFPS(10, 10);
    //     // window.endDrawing();
    }
    game.stop();
    return 0;
}
