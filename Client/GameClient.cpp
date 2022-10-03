/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** GameClient
*/

#include "GameClient.hpp"

GameClient::GameClient()
{

    srand(time(NULL));
    _graphical = std::make_shared<InitSfml>();

    _graphical->setTexture("bg-menu", "Assets/menu/bg-menu.jpeg");
    _graphical->setTexture("logo", "./Assets/menu/logo.png");
    _state = Menu;
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
    _manager.addSystem<ECS::MoveSystem>();
    _manager.addSystem<ECS::CollisionSystem>();
    _manager.addSystem<ECS::TextSystem>();
    _manager.addSystem<ECS::Graphic>();
}

void GameClient::gameLoop()
{
    while (_graphical->getWindow()->isOpen()) {
        while (_graphical->getWindow()->pollEvent(_graphical->getEvent())) {
            const sf::Event &event = _graphical->getEvent();
            handleEvents(event);
        }
        _graphical->clear();
        //paralax
        selectMode();
        _graphical->display();
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
    std::string text = _events.getTextEntered(event);

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
        case GameState::Menu:
                manageMenu();
            break;
        default:
            break;
    }
}

void GameClient::manageMenu()
{
    std::shared_ptr<sf::Texture> sfmlTexture;
    std::shared_ptr<sf::Texture> sfmlTexture2;
    sf::Sprite sprite;
    sfmlTexture = _graphical->getTexture("logo");
    _sprite.setTexture(*sfmlTexture);
    _sprite.setPosition(sf::Vector2f(600, 100));
    sfmlTexture2 = _graphical->getTexture("bg-menu");
    sprite.setTexture(*sfmlTexture2);
    sprite.setScale(sf::Vector2f(1.9, 1.9));
    _graphical->getWindow()->draw(sprite);
    _graphical->getWindow()->draw(_sprite);
}

void GameClient::manageGame()
{

}
