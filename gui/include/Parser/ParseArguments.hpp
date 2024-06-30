/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ParseArguments
*/

#pragma once

#include "IParser.hpp"

class ParseArguments : public IParser {
public:
    ParseArguments(int argc, char *argv[]);
    ~ParseArguments() = default;

    void parse();

    int getArgc() const { return _argc; }
    char **getArgv() const { return _argv; }
    int getPort() const { return _port; }
    void setPort(int port) { _port = port; }
    std::string getMachine() const { return _machine; }
    void setMachine(std::string machine) { _machine = machine; }

    bool isHelp() const { return _isHelp; }
private:
    int _argc;
    char **_argv;
    int _port;
    std::string _machine;

    bool _isHelp;
};
