/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Parser
*/

#include "Parser/ParseArguments.hpp"

ParseArguments::ParseArguments(int argc, char *argv[]) : _argc(argc), _argv(argv), _port(0), _machine(""), _isHelp(false) {}

void ParseArguments::parse()
{
    if (_argc >= 2 && (std::string(_argv[1]) == "-help" || std::string(_argv[1]) == "--help")) {
        _isHelp = true;
        return;
    } else if (_argc != 5)
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
