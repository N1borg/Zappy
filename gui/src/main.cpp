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
#include <iostream>

int main(int argc, char *argv[])
{
    Parser parser;
    Socket socket;
    Window window;

    int screenWidth = window.getScreenWidth();
    int screenHeight = window.getScreenHeight();

    if (argc > 1 && std::string(argv[1]) == "-help") {
        help(std::string(argv[0]));
        return 0;
    }

    try {
        parser = Parser(argc, argv); // Initialize parser with command-line arguments
        if (parser.getMachine().empty() || parser.getPort() <= 0 || parser.getPort() > 65535) {
            throw std::runtime_error("Error: Invalid arguments");
        }

        socket = Socket(parser.getPort(), parser.getMachine()); // Init socket avec parsed port et machine
        socket.connectSocket(); // Connection au serveur

        std::string response = socket.receiveMessage(); // Réception des messages du serveur
        if (parser.parseWelcome(response)) { // On vérifie si c'est "WELCOME"
            socket.sendMessage("GRAPHIC\n"); // On envoie "GRAPHIC"

            window = Window(screenWidth, screenHeight, "Zappy"); // Ouverture de la fenêtre
            window.init();
            window.disableCursor();
            window.setTargetFPS(60);

            // Get map size
            socket.sendMessage("msz\n");
            std::string mapSize = socket.receiveMessage();
            std::cout << "Map size: " << mapSize << std::endl;

            while (!window.shouldClose()) {
                window.parseCameraInputs();
                window.updateCamera();
                window.beginDrawing();
                window.clearBackground(RAYWHITE);
                window.beginMode3D();

                window.drawGrid(10, 1.0f);
                window.drawPlane(Vector3{0, 0, 0}, Vector2{10, 10}, LIGHTGRAY);
                window.drawCube({ 0.0f, 0.0f, 0.0f }, 2.0f, 2.0f, 2.0f, RED);
                window.drawCubeWires({ 0.0f, 0.0f, 0.0f }, 2.0f, 2.0f, 2.0f, MAROON);
                window.endMode3D();
                DrawText("Camera status:", 610, 15, 10, BLACK);
                DrawText(TextFormat("- Mode: %s", (window.getCameraMode() == CAMERA_FREE) ? "FREE" :
                                                (window.getCameraMode() == CAMERA_FIRST_PERSON) ? "FIRST_PERSON" :
                                                (window.getCameraMode() == CAMERA_THIRD_PERSON) ? "THIRD_PERSON" :
                                                (window.getCameraMode() == CAMERA_ORBITAL) ? "ORBITAL" : "CUSTOM"), 610, 30, 10, BLACK);
                DrawText(TextFormat("- Projection: %s", (window.getCamera().projection == CAMERA_PERSPECTIVE) ? "PERSPECTIVE" :
                                                        (window.getCamera().projection == CAMERA_ORTHOGRAPHIC) ? "ORTHOGRAPHIC" : "CUSTOM"), 610, 45, 10, BLACK);
                DrawText(TextFormat("- Position: (%06.3f, %06.3f, %06.3f)", window.getCamera().position.x, window.getCamera().position.y, window.getCamera().position.z), 610, 60, 10, BLACK);
                DrawText(TextFormat("- Target: (%06.3f, %06.3f, %06.3f)", window.getCamera().target.x, window.getCamera().target.y, window.getCamera().target.z), 610, 75, 10, BLACK);
                DrawText(TextFormat("- Up: (%06.3f, %06.3f, %06.3f)", window.getCamera().up.x, window.getCamera().up.y, window.getCamera().up.z), 610, 90, 10, BLACK);
                window.endDrawing();

                // std::string serverResponse = socket.receiveMessage();
                // printf("Server response: %s\n", serverResponse.c_str());
            }

            window.close();
        } else {
            std::cerr << "Error: Failed to parse welcome message." << std::endl;
            return 84;
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
