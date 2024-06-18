/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** Socket
*/

#include "Socket.hpp"

Socket::Socket(int port, const std::string machine) : _port(port), _machine(machine), _clientSocket(0), _connected(false) {}

Socket::~Socket()
{
    if (_clientSocket != -1)
        close(_clientSocket);
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

bool Socket::isConnected() const
{
    return _connected.load();
}

bool Socket::connectSocket()
{
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(_port);

    _clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (_clientSocket == -1)
        return false;
    if (inet_pton(AF_INET, _machine.c_str(), &serverAddress.sin_addr) <= 0)
        return false;
    if (connect(_clientSocket, (struct sockaddr*)(&serverAddress), sizeof(serverAddress)) == -1)
        return false;
    return true;
}

void Socket::sendMessage(const std::string &message)
{
    if (_clientSocket == -1)
        throw std::runtime_error("Socket is not connected");

    ssize_t bytesSent = send(_clientSocket, message.c_str(), message.size(), 0);
    if (bytesSent == -1)
        throw std::runtime_error("Failed to send message: " + std::string(strerror(errno)));
}

std::string Socket::receiveMessage()
{
    if (_clientSocket == -1)
        throw std::runtime_error("Socket is not connected");

    char buffer[1024] = {0};
    ssize_t bytesReceived = recv(_clientSocket, buffer, 1024, 0);
    if (bytesReceived == -1)
        throw std::runtime_error("Failed to receive message: " + std::string(strerror(errno)));
    return std::string(buffer);
}

void Socket::attemptConnection()
{
    while (!_connected) {
        _connected = connectSocket();
        if (!_connected)
            std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}
