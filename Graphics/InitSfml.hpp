/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** InitSfml
*/

#ifndef INITSFML_HPP_
#define INITSFML_HPP_

#include <string>

class InitSfml {
    public:
        InitSfml(int widthWindow = 1920, int heightWindow = 1080, const std::string &nameWindow = "R-Type");
        ~InitSfml() = default;
        std::shared_ptr<sf::RenderWindow> getWindow();
        sf::Event &getEvent();
        void clear();
        void display();

    protected:
    private:
        std::shared_ptr<sf::RenderWindow> _window;
};

#endif /* !INITSFML_HPP_ */
