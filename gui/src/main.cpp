/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** main
*/

#include "../include/main.hpp"
#include "../include/Parser.hpp"
#include "../include/Socket.hpp"
#include "../include/Window.hpp"

int main(int argc, char *argv[])
{
    Parser parser;
    Socket socket;
    Window window;

    if (argc > 1 && std::string(argv[1]) == "-help") {
        help(std::string(argv[0]));
        return 0;
    }
    try {
        parser = Parser(argc, argv);
        if (parser.getMachine().empty() || parser.getPort() <= 0 || parser.getPort() > 65535) {
            throw std::runtime_error("Error: Invalid arguments");
            return 84;
        }
        socket = Socket(parser.getPort(), parser.getMachine());
        socket.connectSocket();
        socket.sendMessage("GRAPHIC");

        window = Window(800, 600, "Zappy");
        window.init();
        window.setTargetFPS(60);

        while (!window.shouldClose()) {
            window.beginDrawing();
            window.clearBackground(RAYWHITE);
            window.updateCamera();
            window.beginMode3D();
            window.drawCube({ 0.0f, 0.0f, 0.0f }, 2.0f, 2.0f, 2.0f, RED);
            window.drawCubeWires({ 0.0f, 0.0f, 0.0f }, 2.0f, 2.0f, 2.0f, MAROON);
            window.drawGrid(10, 1.0f);
            window.endMode3D();
            window.endDrawing();
        }

        window.close();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
