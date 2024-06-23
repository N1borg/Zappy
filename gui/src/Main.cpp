/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** main
*/

#include "Game/Game.hpp"

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
}
