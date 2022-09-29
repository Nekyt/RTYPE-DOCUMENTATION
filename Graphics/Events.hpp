/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** Events
*/

#ifndef EVENTS_HPP_
#define EVENTS_HPP_

#include <map>

enum class Button {
        Left,
        Right,
        Up,
        Down,
        Q,
        Z,
        S,
        D,
        Start,
        Select,
        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        None,
};

class Events {
    public:
        Events() = default;
        ~Events() = default;

    protected:
    private:
        static const std::map<Button, sf::Keyboard::Key> eventsButton;
};

#endif /* !EVENTS_HPP_ */
