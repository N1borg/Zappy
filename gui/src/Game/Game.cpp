/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Game
*/

#include "Game/Game.hpp"

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
    if (!_welcomeReceived || !_mapSizeReceived) {
        _window->waitingScreen(elapsedTime);
    } else {
        RaylibWrapper::beginDrawing();
        RaylibWrapper::clearBackground(SKYBLUE);
        //     // if (window.isMouseButtonPressed(MOUSE_LEFT_BUTTON) || window.isKeyPressed(KEY_ENTER))
        //     //     map.selectTile(GetMouseRay({window.getScreenWidth() / 2.0f, window.getScreenHeight() / 2.0f}, window.getCamera()));

        RaylibWrapper::updateCamera(getWindow()->getCamera()->getCameraObj(), (getWindow()->getCamera()->getCameraMode()));
        RaylibWrapper::beginMode3D(*getWindow()->getCamera()->getCameraObj());
        RaylibWrapper::drawGrid(20, 10.0f);
        getMap()->draw();
        getMap()->drawTransparent();
        RaylibWrapper::endMode3D();

        //     // window.drawText(TextFormat("X:%f Y:%f Z:%f", window.getCamera().position.x, window.getCamera().position.y, window.getCamera().position.z), 10, 40, 20, GRAY);

        getWindow()->drawCrosshair();
        RaylibWrapper::drawFPS(10, 10);
        RaylibWrapper::endDrawing();
    }
}

void Game::parseInputs()
{
    switch (RaylibWrapper::getKeyPressed()) {
        case KEY_ONE:
            _window->getCamera()->setCameraMode(CAMERA_FIRST_PERSON);
            _window->getCamera()->setCameraUp({0.0f, 1.0f, 0.0f});
            break;
        case KEY_TWO:
            _window->getCamera()->setCameraMode(CAMERA_THIRD_PERSON);
            _window->getCamera()->setCameraUp({0.0f, 1.0f, 0.0f});
            break;
        case KEY_THREE:
            _window->getCamera()->setCameraMode(CAMERA_FREE);
            _window->getCamera()->setCameraUp({0.0f, 1.0f, 0.0f});
            break;
        case KEY_FOUR:
            _window->getCamera()->setCameraMode(CAMERA_ORBITAL);
            _window->getCamera()->setCameraUp({0.0f, 1.0f, 0.0f});
            break;
        default:
            break;
    }
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

bool Game::hasError() const
{
    return _isError;
}

void Game::setWelcomeReceived(bool welcomeReceived)
{
    _welcomeReceived = welcomeReceived;
}

void Game::setMapSizeReceived(bool mapSizeReceived)
{
    _mapSizeReceived = mapSizeReceived;
}
