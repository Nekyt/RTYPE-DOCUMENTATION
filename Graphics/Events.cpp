/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** Events
*/

#include "Events.hpp"

const std::map<sf::Keyboard::Key, Button> Events::eventsButton = {
    std::make_pair(sf::Keyboard::Left, Button::Left),
    std::make_pair(sf::Keyboard::Right, Button::Right),
    std::make_pair(sf::Keyboard::Up, Button::Up),
    std::make_pair(sf::Keyboard::Down, Button::Down),
    std::make_pair(sf::Keyboard::Q, Button::Q),
    std::make_pair(sf::Keyboard::D, Button::D),
    std::make_pair(sf::Keyboard::Z, Button::Z),
    std::make_pair(sf::Keyboard::S, Button::S),
    std::make_pair(sf::Keyboard::Enter, Button::Enter),
    std::make_pair(sf::Keyboard::F1, Button::F1),
    std::make_pair(sf::Keyboard::F2, Button::F2),
    std::make_pair(sf::Keyboard::F3, Button::F3),
    std::make_pair(sf::Keyboard::F4, Button::F4),
    std::make_pair(sf::Keyboard::F5, Button::F5),
    std::make_pair(sf::Keyboard::F6, Button::F6),
    std::make_pair(sf::Keyboard::F7, Button::F7),
};

Button Events::getEventType(const sf::Event &event) const
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (eventsButton.find(event.key.code) != eventsButton.end())
            return eventsButton.at(event.key.code);
        else
            return Button::None;
    }
    return Button::None;
}

std::string Events::getTextEntered(const sf::Event &event) const
{
    if (event.type == sf::Event::TextEntered)
    {
        if (event.text.unicode < 128 && event.text.unicode != 8 && event.text.unicode != 13)
        {
            return std::string(1, static_cast<char>(event.text.unicode));
        }
    }
    return "";
}
