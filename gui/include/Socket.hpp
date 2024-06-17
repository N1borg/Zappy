/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** Socket
*/

#pragma once
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

class Socket {
    public:
        Socket();
        Socket(int port, std::string machine);
        ~Socket();

        void setPort(int port);
        int getPort() const;
        void setMachine(std::string machine);
        std::string getMachine() const;

        void connectSocket();
        void sendMessage(const std::string &message);
        std::string receiveMessage();

    private:
        int _port;
        std::string _machine;
        int _clientSocket;
};
