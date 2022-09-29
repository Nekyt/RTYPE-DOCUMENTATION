/*
** EPITECH PROJECT, 2022
** B-CPP-500-STG-5-1-rtype-romanie.de-meyer
** File description:
** system
*/

#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include <iostream>
#include <utility>
#include "../entyti.hpp"
#include <cstdio>
#include <SFML/Graphics.hpp>

class Manager{};

class Graphic
{
    public:
        void preupdate();
        void update();
        void postupdate();
    private:
        Manager *m_system;
        sf::RenderWindow *m_window;
};

#endif /* !SYSTEM_HPP_ */
