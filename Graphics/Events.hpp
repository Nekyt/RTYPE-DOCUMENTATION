/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** Events
*/

#ifndef EVENTS_HPP_
#define EVENTS_HPP_

#include "SFML/Graphics.hpp"
#include <map>
#include <string>

enum class Button {
    Left,
    Right,
    Up,
    Down,
    Q,
    Z,
    S,
    D,
    Enter,
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    None,
};

enum class Mouse {
    None,
    Left,
    Right,
};

class Events {
    public:
        Events() = default;
        ~Events() = default;

        Button getEventType(const sf::Event &event) const;
        std::string getTextEntered(const sf::Event &event) const;
        Mouse getEventTypeMouse(const sf::Event &event) const;

    protected:
    private:
        static const std::map<sf::Keyboard::Key, Button> eventsButton;
        static const std::map<sf::Mouse::Button, Mouse> eventsMouse;
};

#endif /* !EVENTS_HPP_ */
