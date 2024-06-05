/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Window
*/

#include "../include/Window.hpp"

Window::Window()
{
}

Window::Window(int width, int height, std::string title)
{
    _width = width;
    _height = height;
    _title = title;
    // _camera = {0};
}

Window::~Window()
{
}
