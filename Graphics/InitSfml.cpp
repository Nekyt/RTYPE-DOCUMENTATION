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

void InitSfml::setSprite(std::string idSprite, std::string namePath)
{
    sf::Texture texture;
    sf::Sprite sprite;

    texture.loadFromFile(namePath);
    sprite.setTexture(texture);
    _spriteList.emplace(idSprite, std::make_shared<sf::Sprite>(sprite));
}

std::shared_ptr<sf::Sprite> InitSfml::getSprite(std::string idSprite)
{
    return _spriteList.at(idSprite);
}

std::map<std::string, std::shared_ptr<sf::Sprite>> InitSfml::getAllSprite()
{
    return _spriteList;
}

void InitSfml::clear()
{
    _window->clear();
}

void InitSfml::display()
{
    _window->display();
}
