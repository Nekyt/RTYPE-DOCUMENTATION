/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** GameClient
*/

#include "GameClient.hpp"

GameClient::GameClient()
{
    _graphical = std::make_shared<InitSfml>();
}

void GameClient::gameLoop()
{
    while (_graphical->getWindow()->isOpen()) {
        while (_graphical->getWindow()->pollEvent(_graphical->getEvent())) {
            const sf::Event &event = _graphical->getEvent();
            handleEvents(event);
        }
        //clear
        //update
    }
}

void GameClient::handleEvents(const sf::Event &event)
{
    if (event.type == sf::Event::Closed)
        _graphical->getWindow()->close();
    else if (event.type == sf::Event::KeyPressed) {
        //button
    } else if (event.type == sf::Event::TextEntered)
        //text
}