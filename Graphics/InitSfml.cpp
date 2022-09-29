/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** InitSfml
*/

#include "InitSfml.hpp"

InitSfml::InitSfml(int widthWindow, int heightWindow, const std::string &nameWindow)
{
    _window = std::make_shared<sf::RenderWindow>(sf::VideoMode(widthWindow, heightWindow), nameWindow);
    _window->setFramerateLimit(60);
}

sf::Event &InitSfml::getEvent()
{
    return _event;
}

std::shared_ptr<sf::RenderWindow> InitSfml::getWindow()
{
    return _window;
}

void InitSfml::clear()
{
    _window->clear();
}

void InitSfml::display()
{
    _window->display();
}
