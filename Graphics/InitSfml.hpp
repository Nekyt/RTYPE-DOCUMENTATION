/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** InitSfml
*/

#ifndef INITSFML_HPP_
#define INITSFML_HPP_

#include <string>
#include <memory>
#include <map>
#include "SFML/Graphics.hpp"

class InitSfml {
    public:
        InitSfml(int widthWindow = 1920, int heightWindow = 1080, const std::string &nameWindow = "R-Type");
        ~InitSfml() = default;
        std::shared_ptr<sf::RenderWindow> getWindow();
        sf::Event &getEvent();

        void setSprite(std::string idSprite, std::string namePath);
        std::shared_ptr<sf::Sprite> getSprite(std::string idSprite);
        std::map<std::string, std::shared_ptr<sf::Sprite>> getAllSprite();

        void clear();
        void display();

    protected:
    private:
        std::shared_ptr<sf::RenderWindow> _window;
        std::map<std::string, std::shared_ptr<sf::Sprite>> _spriteList;
};

#endif /* !INITSFML_HPP_ */
