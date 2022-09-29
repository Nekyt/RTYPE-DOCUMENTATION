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

class Manager
{
    public:
        void set_texture(std::string){};
        int get_id(){return (0);};
        void set_size(int,int){};
        void set_size_sprite(int,int,int,int);
        int get_size_sprite();
        int get_position_x();
        int get_position_y();
        std::string get_texture();
        void set_rotate(int);
}
;

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
