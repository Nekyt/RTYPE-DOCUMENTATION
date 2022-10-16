/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** Events
*/

#include "Events.hpp"

/* It's a map of the sfml keycodes to the Button enum. */
const std::map<sf::Keyboard::Key, Button> Events::eventsButton = {
    std::make_pair(sf::Keyboard::Left, Button::Left),
    std::make_pair(sf::Keyboard::Right, Button::Right),
    std::make_pair(sf::Keyboard::Up, Button::Up),
    std::make_pair(sf::Keyboard::Down, Button::Down),
    std::make_pair(sf::Keyboard::Space, Button::Space),
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

/* It's a map of the sfml mouse button codes to the Mouse enum. */
const std::map<sf::Mouse::Button, Mouse> Events::eventsMouse = {
    std::make_pair(sf::Mouse::Left, Mouse::Left),
    std::make_pair(sf::Mouse::Right, Mouse::Right),
};

/**
 * If the event type is a key press, and the key pressed is in the map, return the
 * value of the key pressed in the map
 *
 * @param event The event to check.
 *
 * @return the Button type.
 */
Button Events::getEventType(const sf::Event& event) const
{
    if (event.type == sf::Event::KeyPressed) {
        if (eventsButton.find(event.key.code) != eventsButton.end())
            return eventsButton.at(event.key.code);
        else
            return Button::None;
    }
    return Button::None;
}

/**
 * If the event is a text entered event, and the unicode value is a valid ASCII
 * character, return the character as a string
 *
 * @param event The event to check.
 *
 * @return A string of the character that was entered.
 */
std::string Events::getTextEntered(const sf::Event& event) const
{
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode < 128 && event.text.unicode != 8 && event.text.unicode != 13) {
            return std::string(1, static_cast<char>(event.text.unicode));
        }
    }
    return "";
}

/**
 * If the event type is a mouse button release, and the mouse button is in the map,
 * return the mapped value, otherwise return None
 *
 * @param event The event to check.
 *
 * @return The event type of the mouse.
 */
Mouse Events::getEventTypeMouse(const sf::Event& event) const
{
    if (event.type == sf::Event::MouseButtonReleased) {
        if (eventsMouse.find(event.mouseButton.button) != eventsMouse.end())
            return eventsMouse.at(event.mouseButton.button);
        else
            return Mouse::None;
    }
    return Mouse::None;
}
