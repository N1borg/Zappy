/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** main
*/

#include "../include/main.hpp"
#include "../include/Parser.hpp"
#include "../include/Socket.hpp"

int main(int argc, char *argv[])
{
    Parser parser;
    Socket socket;

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
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
