/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** Parser
*/

#include "ParseArguments.hpp"

ParseArguments::ParseArguments(int argc, char *argv[]) : _argc(argc), _argv(argv) {}

void ParseArguments::parse()
{
    if (_argc != 5)
        throw std::runtime_error("Error: Invalid arguments");

    try {
        if (std::string(_argv[1]) == "-p" && std::string(_argv[3]) == "-h") {
            _port = std::stoi(_argv[2]);
            _machine = std::string(_argv[4]);
        }
        if (std::string(_argv[1]) == "-h" && std::string(_argv[3]) == "-p") {
            _port = std::stoi(_argv[4]);
            _machine = std::string(_argv[2]);
        }
    } catch (const std::exception &e) {
        throw std::runtime_error("Error: Invalid arguments");
    }
}

void ParseArguments::setPort(int port)
{
    _port = port;
}

int ParseArguments::getPort() const
{
    return _port;
}

void ParseArguments::setMachine(std::string machine)
{
    _machine = machine;
}

std::string ParseArguments::getMachine() const
{
    return _machine;
}
