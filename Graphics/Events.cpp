/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** Events
*/

#include "Events.hpp"

const std::map<Button, sf::Keyboard::key> Events::eventsButton = {
    std::make_pair(Button::Left, sf::Keyboard::Left),
    std::make_pair(Button::Right, sf::Keyboard::Right),
    std::make_pair(Button::Up, sf::Keyboard::Up),
    std::make_pair(Button::Down, sf::Keyboard::Down),
    std::make_pair(Button::Q, sf::Keyboard::Q),
    std::make_pair(Button::D, sf::Keyboard::D),
    std::make_pair(Button::Z, sf::Keyboard::Z),
    std::make_pair(Button::S, sf::Keyboard::S),
    std::make_pair(Button::Start, sf::Keyboard::C),
    std::make_pair(Button::Select, sf::Keyboard::V),
    std::make_pair(Button::F1, sf::Keyboard::F1),
    std::make_pair(Button::F2, sf::Keyboard::F2),
    std::make_pair(Button::F3, sf::Keyboard::F3),
    std::make_pair(Button::F4, sf::Keyboard::F4),
    std::make_pair(Button::F5, sf::Keyboard::F5),
    std::make_pair(Button::F6, sf::Keyboard::F6),
    std::make_pair(Button::F7, sf::Keyboard::F7),
};

Button SfmlEventFactory::getEventType(const sf::Event &event) const
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (eventType.find(event.key.code) != eventType.end())
            return eventType.at(event.key.code);
        else
            return Button::None;
    }
    return Button::None;
}

std::string SfmlEventFactory::getTextEntered(const sf::Event &event) const
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
