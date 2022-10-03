/*
** EPITECH PROJECT, 2022
** B-CPP-500-STG-5-1-rtype-romanie.de-meyer
** File description:
** system
*/

#include "system.hpp"
#include <cstdio>
#include <SFML/Graphics.hpp>

void Input::preupdate()
{
    sf::Event event;

    while (m_window->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                m_window->close();
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                    case sf::Keyboard::Escape:
                        m_window->close();
                        break;
                    case sf::Keyboard::Left:
                        m_system->set_speed_y = -5;
                    case sf::Keyboard::Right:
                        m_system->set_speed_y = 5;
                    case sf::Keyboard::Up:
                        m_system->set_speed_x = -5;
                    case sf::Keyboard::Down:
                        m_system->set_speed_x = 5;
                    default:
                        m_system->set_speed_x = 0;
                        m_system->set_speed_y = 0;
                        break;
                }
                break;
            case sf::Event::MouseButtonPressed:
                switch (event.mouseButton.button) {
                    case sf::Mouse::Left:
                        break;
                    default:
                        break;

                }

        }
    }
}