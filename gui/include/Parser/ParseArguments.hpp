/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
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
    bool validateConnection(std::string msg);

    int getPort() const;
    void setPort(int port);
    std::string getMachine() const;
    void setMachine(std::string machine);
private:
    int _argc;
    char **_argv;
    int _port;
    std::string _machine;
};
