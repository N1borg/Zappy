/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Game
*/

#include "Game.hpp"

Game::Game(Socket *socket) : _socket(socket)
{
    _window = new Window(1280, 720, "Zappy GUI");
    _map = new Map();
}

void Game::init()
{
    _window->init();
    _socket->startThread(this);

    if (!_window->waitingConnection(*_socket, _socket->getMachine(), false))
        _isError = true;
}

void Game::stop()
{
    RaylibWrapper::closeWindow();
    _socket->stopThread();
    _map->unload();
}

void Game::render(float elapsedTime)
{
    RaylibWrapper::beginDrawing();
    RaylibWrapper::clearBackground(RAYWHITE);

    if (!_welcomeReceived || !_mapSizeReceived) {
        _window->waitingScreen(elapsedTime);
    } else {
        _map->draw();
    }

    RaylibWrapper::endDrawing();
}

Window *Game::getWindow()
{
    return _window;
}

Socket *Game::getSocket()
{
    return _socket;
}

Map *Game::getMap()
{
    return _map;
}

void Game::setWelcomeReceived(bool welcomeReceived)
{
    _welcomeReceived = welcomeReceived;
}

void Game::setMapSizeReceived(bool mapSizeReceived)
{
    _mapSizeReceived = mapSizeReceived;
}
