/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** ParseArguments
*/

#pragma once

#include <iostream>
#include "IParser.hpp"

class ParseArguments: public IParser {
    public:
        ParseArguments(int argc, char *argv[]);
        ~ParseArguments() = default;

        void parse();

        // Getters
        int getPort() const;
        std::string getMachine() const;

        // Setters
        void setPort(int port);
        void setMachine(std::string machine);
    private:
        int _argc;
        char **_argv;
        int _port;
        std::string _machine;
};
