#include "Game/Game.hpp"

// Initialise le jeu avec un socket et crée les composants de la fenêtre et de la carte.
Game::Game(Socket *socket) : _socket(socket)
{
    _window = new Window(1280, 720, "Zappy GUI");
    _map = new Map();
}

// Initialise les composants du jeu et démarre le thread réseau.
void Game::init()
{
    _window->init();
    _socket->startThread(this);

    if (!_window->waitingConnection(*_socket, _socket->getMachine(), false))
        _isError = true;
}

// Arrête tous les composants du jeu et ferme la fenêtre.
void Game::stop()
{
    _window->close();
    _socket->stopThread();
    _map->unload();
}

// Gère le rendu du jeu en fonction de l'état de la réception des messages.
void Game::render(float elapsedTime)
{
    if (!_welcomeReceived || !_mapSizeReceived) {
        _window->waitingScreen(elapsedTime);
    } else {
        RaylibWrapper::beginDrawing();
        RaylibWrapper::clearBackground(SKYBLUE);
        RaylibWrapper::updateCamera(getWindow()->getCamera()->getCameraObj(), (getWindow()->getCamera()->getCameraMode()));
        RaylibWrapper::beginMode3D(*getWindow()->getCamera()->getCameraObj());
        RaylibWrapper::drawGrid(20, 10.0f);
        getMap()->draw();
        getMap()->drawTransparent();
        RaylibWrapper::endMode3D();

        getWindow()->drawGeneralInfo(*getMap());
        if (getMap()->isTileSelected())
            getWindow()->drawTileInfo(getMap()->getSelectedTile());
        getWindow()->drawCrosshair();
        RaylibWrapper::drawFPS(10, 10);
        RaylibWrapper::endDrawing();
    }
}

// Traite les entrées utilisateur pour interagir avec le jeu.
void Game::parseInputs()
{
    switch (RaylibWrapper::getKeyPressed()) {
        case MOUSE_LEFT_BUTTON:
            _map->selectTile(RaylibWrapper::getMouseRay({RaylibWrapper::getScreenWidth() / 2.0f, RaylibWrapper::getScreenHeight() / 2.0f}, *getWindow()->getCamera()->getCameraObj()));
            break;
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

// Retourne le composant Window du jeu.
Window *Game::getWindow()
{
    return _window;
}

// Retourne le socket utilisé par le jeu.
Socket *Game::getSocket()
{
    return _socket;
}

// Retourne le composant Map du jeu.
Map *Game::getMap()
{
    return _map;
}

// Vérifie si une erreur est survenue pendant l'exécution du jeu.
bool Game::hasError() const
{
    return _isError;
}

// Définit l'état de réception du message de bienvenue.
void Game::setWelcomeReceived(bool welcomeReceived)
{
    _welcomeReceived = welcomeReceived;
}

// Définit l'état de réception de la taille de la carte.
void Game::setMapSizeReceived(bool mapSizeReceived)
{
    _mapSizeReceived = mapSizeReceived;
}

// Définit l'unité de temps pour les opérations du jeu.
void Game::setTimeUnit(int timeUnit)
{
    _timeUnit = timeUnit;
}
