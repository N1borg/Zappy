/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** Parser
*/

#pragma once

#include <iostream>
#include <string>
#include <stdexcept>

class Parser {
    public:
        Parser() = default;
        Parser(int argc, char *argv[]);
        ~Parser() = default;

        void setPort(int port);
        int getPort() const;
        void setMachine(std::string machine);
        std::string getMachine() const;
        bool parseWelcome(const std::string& message);

    private:
        int _port;
        std::string _machine;
};