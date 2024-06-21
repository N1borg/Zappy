/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** Socket
*/

#include "Socket.hpp"

Socket::Socket(int port, std::string machine) : _port(port), _machine(machine), _clientSocket(-1), _connected(false), _threadRunning(false) {}

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
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

std::string Socket::receiveMessage()
{
    if (_clientSocket == -1)
        throw std::runtime_error("Socket is not connected");

    struct timeval tv;
    tv.tv_sec = 3;
    tv.tv_usec = 0;

    // Define socket timeout
    if (setsockopt(_clientSocket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof(tv)) < 0)
        throw std::runtime_error("Failed to set socket timeout: " + std::string(strerror(errno)));

    char buffer[1024] = {0};
    ssize_t bytesReceived = recv(_clientSocket, buffer, 1024, 0);
    if (bytesReceived == -1) {
        if (errno == EAGAIN || errno == EWOULDBLOCK)
            return "";
        throw std::runtime_error("Failed to receive message: " + std::string(strerror(errno)));
    }
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

void Socket::startThread()
{
    _threadRunning = true;
    _thread = std::thread(&Socket::readThread, this);
}

void Socket::stopThread()
{
    _threadRunning = false;
    if (_thread.joinable())
        _thread.join();
}

void Socket::readThread()
{
    ParseCommands cmdParser;

    while (_threadRunning) {
        if (!_connected)
            attemptConnection();
        std::string message = receiveMessage();
        if (message.empty())
            _connected = false;
        else
            cmdParser.parse(message);
    }
}
