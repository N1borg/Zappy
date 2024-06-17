/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** Socket
*/

#include "../include/Socket.hpp"

Socket::Socket() : _port(0), _machine(""), _clientSocket(0) {}

Socket::Socket(int port, const std::string machine) : _port(port), _machine(machine), _clientSocket(0) {}

Socket::~Socket()
{
    if (_clientSocket != -1) {
        close(_clientSocket);
    }
}

void Socket::setPort(int port)
{
    _port = port;
}

int Socket::getPort() const
{
    return _port;
}

void Socket::setMachine(std::string machine)
{
    _machine = machine;
}

std::string Socket::getMachine() const
{
    return _machine;
}

void Socket::connectSocket()
{
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(_port);

    _clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (_clientSocket == -1) {
        throw std::runtime_error("Failed to create socket: " + std::string(strerror(errno)));
    }
    if (inet_pton(AF_INET, _machine.c_str(), &serverAddress.sin_addr) <= 0) {
        throw std::runtime_error("Invalid IP address: " + _machine + ": " + std::string(strerror(errno)));
    }
    
    if (connect(_clientSocket, (struct sockaddr*)(&serverAddress), sizeof(serverAddress)) == -1) {
        throw std::runtime_error("Failed to connect to server: " + std::string(strerror(errno)));
    }
}

void Socket::sendMessage(const std::string &message)
{
    if (_clientSocket == -1) {
        throw std::runtime_error("Socket is not connected");
    }
    ssize_t bytesSent = send(_clientSocket, message.c_str(), message.size(), 0);
    if (bytesSent == -1) {
        throw std::runtime_error("Failed to send message: " + std::string(strerror(errno)));
    }
}

std::string Socket::receiveMessage()
{
    char buffer[1024];
    std::memset(buffer, 0, sizeof(buffer));
    ssize_t bytesRead = recv(_clientSocket, buffer, sizeof(buffer) - 1, 0);
    if (bytesRead == -1) {
        throw std::runtime_error("Failed to receive message: " + std::string(strerror(errno)));
    }
    return std::string(buffer, bytesRead);
}