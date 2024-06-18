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
#include <thread>
#include <atomic>

class Socket {
public:
    Socket(int port, std::string machine);
    ~Socket();

    void setPort(int port);
    int getPort() const;
    void setMachine(std::string machine);
    std::string getMachine() const;
    bool isConnected() const;

    bool connectSocket();
    void sendMessage(const std::string &message);
    void attemptConnection();

private:
    int _port;
    std::string _machine;
    int _clientSocket;
    std::atomic<bool> _connected;
};
