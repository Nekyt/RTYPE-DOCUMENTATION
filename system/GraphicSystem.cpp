/*
** EPITECH PROJECT, 2022
** B-CPP-500-STG-5-1-rtype-romanie.de-meyer
** File description:
** system
*/

#include "GraphicSystem.hpp"

void Graphic::preupdate()
{
    m_window->clear(sf::Color::Black);
    if (m_system->get_id() = 0)
        m_system->set_texture("r-typesheet1-0.png");
        m_system->set_size_sprite(0,0,10,10);
    if (m_system->get_id() = 1)
        m_system->set_texture("r-typesheet1-0.png");
        m_system->set_size_sprite(0,0,10,10);
    m_system->set_rotate(0);
    m_system->set_size(10,10);
}

void Graphic::update()
{
    sf::Texture texture;
    texture.loadFromFile(m_system->get_texture());
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(m_system->get_size_sprite()));
    sprite.setPosition(m_system->get_position_x(), m_system->get_position_y());
    m_window.draw(sprite);
}

void Graphic::postupdate()
{
    m_window->display();
}