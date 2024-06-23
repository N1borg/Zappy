/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Game
*/

#pragma once

#include "Window.hpp"
#include "Socket.hpp"
#include "Map.hpp"
#include "Commands/Commands.hpp"
#include "RaylibWrapper.hpp"

class Game {
    public:
        Game() = default;
        Game(Socket *socket);
        ~Game() = default;

        // Other
        void init();
        void stop();
        void render(float elapsedTime);
        void parseInputs();

        // Getters
        Window *getWindow();
        Socket *getSocket();
        Map *getMap();
        bool hasError() const;
        int getTimeUnit() const;

        // Setters
        void setWelcomeReceived(bool welcomeReceived);
        void setMapSizeReceived(bool mapSizeReceived);
        void setTilesReceived(bool tilesReceived);
        void setPlayersReceived(bool playersReceived);
        void setTimeUnitReceived(bool timeUnitReceived);
        void setTimeUnit(int timeUnit);

    protected:
        Window *_window;
        Socket *_socket;
        Map *_map;
        bool _isError = false;
        bool _welcomeReceived = false;
        bool _mapSizeReceived = false;
        bool _tilesReceived = false;
        bool _playersReceived = false;
        bool _timeUnitReceived = false;
        bool _isConnected = false;
        int _timeUnit = 0;
};
