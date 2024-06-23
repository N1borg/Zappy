/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include <Window.hpp>
#include <Socket.hpp>
#include <Map.hpp>
#include "Commands/Commands.hpp"

class Game {
    public:
        Game() = default;
        Game(Socket *socket);
        ~Game() = default;

        // Other
        void init();
        void stop();

        // Getters
        Window *getWindow();
        Socket *getSocket();
        Map *getMap();

        // Setters
        void setWelcomeReceived(bool welcomeReceived);
        void setMapSizeReceived(bool mapSizeReceived);

    protected:
        Window *_window;
        Socket *_socket;
        Map *_map;
        bool _isError = false;
        bool _welcomeReceived = false;
        bool _mapSizeReceived = false;
};

#endif /* !GAME_HPP_ */
