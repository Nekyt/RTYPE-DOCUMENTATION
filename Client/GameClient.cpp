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
    _graphical.setSprite("bg-menu", "Assets/menu/bg-menu.jpeg");
    _graphical.setSprite("logo", "Assets/menu/logo.png");
    //load sprite start
    //load text and music
    loadComponents();
    loadSystems();
}

void GameClient::loadComponents()
{
    //load component
}

void GameClient::loadSystems()
{
    //load systems
}

void GameClient::gameLoop()
{
    while (_graphical->getWindow()->isOpen()) {
        while (_graphical->getWindow()->pollEvent(_graphical->getEvent())) {
            const sf::Event &event = _graphical->getEvent();
            handleEvents(event);
        }
        _graphical.clear();
        //paralax
        selectMode();
        _graphical.display();
    }
}

void GameClient::handleEvents(const sf::Event &event)
{
    Button eventKey = _events.getEventType(event);

    if (event.type == sf::Event::Closed)
        _graphical->getWindow()->close();
    else if (event.type == sf::Event::KeyPressed && eventKey != Button::None)
        handleEventsKey(eventKey);
    else if (event.type == sf::Event::TextEntered && eventKey == Button::None)
        handleEventsTextEntered(event);
}

void GameClient::handleEventsKey(Button eventKey)
{
    switch (_state) {
        case GameState::Game:
            //handle game
            break;
        default:
            break;
    }
}

void GameClient::handleEventsTextEntered(const sf::Event &event)
{
    std::string text = _events.getTextEntered();

    switch (_state) {
        case GameState::Game:
            //handleEventsTextEntered game
            break;
        default:
            break;
    }
}

void GameClient::selectMode()
{
    switch (_state) {
        case GameState::Game:
            //selectMode game
            break;
        default:
            break;
    }
}
