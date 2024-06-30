/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Socket
*/

#pragma once

#include "Parser/ParseCommands.hpp"

#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <atomic>

class Socket {
public:
    Socket(int port, std::string machine) : _port(port), _machine(machine), _clientSocket(-1), _connected(false), _threadRunning(false) {}
    ~Socket() { if (_clientSocket != -1) { close(_clientSocket); } }

    int getPort() const { return _port; }
    void setPort(int port) { _port = port; }
    std::string getMachine() const { return _machine; }
    void setMachine(std::string machine) { _machine = machine; }
    bool isConnected() const { return _connected.load(); }

    // Socket
    bool connectSocket();
    void sendMessage(const std::string &message);
    std::string receiveMessage();
    void attemptConnection();

    // Thread
    void startThread(std::shared_ptr<Map> map);
    void stopThread();
    void readThread();
private:
    int _port;
    std::string _machine;
    int _clientSocket;
    std::atomic<bool> _connected;
    std::atomic<bool> _threadRunning;
    std::thread _thread;
    std::shared_ptr<Map> _map;
};
