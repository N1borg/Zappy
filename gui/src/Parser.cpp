/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** Parser
*/

#include "../include/Parser.hpp"
#include "../include/main.hpp"

Parser::Parser(int argc, char *argv[])
{
    if (argc != 5) {
        throw std::runtime_error("Error: Invalid arguments");
    }
    try {
        if (std::string(argv[1]) == "-p" && std::string(argv[3]) == "-h") {
            _port = std::stoi(argv[2]);
            _machine = std::string(argv[4]);
        }
        else if (std::string(argv[1]) == "-h" && std::string(argv[3]) == "-p") {
            _port = std::stoi(argv[4]);
            _machine = std::string(argv[2]);
        } else {
            throw std::runtime_error("Error: Invalid arguments");
        }
    } catch (const std::exception &e) {
        throw std::runtime_error("Error: Invalid arguments");
    }
}

bool Parser::parseWelcome(const std::string& message) {
    return message == "WELCOME\n";
}

void Parser::setPort(int port)
{
    _port = port;
}

int Parser::getPort() const
{
    return _port;
}

void Parser::setMachine(std::string machine)
{
    _machine = machine;
}

std::string Parser::getMachine() const
{
    return _machine;
}
