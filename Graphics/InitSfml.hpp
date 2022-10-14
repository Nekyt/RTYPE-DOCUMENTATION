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
#include <SFML/Graphics.hpp>
// #include <SFML/Audio.hpp>

class InitSfml {
    public:
        InitSfml(int widthWindow = 1920, int heightWindow = 1080, const std::string &nameWindow = "R-Type");
        ~InitSfml() = default;
        std::shared_ptr<sf::RenderWindow> getWindow();
        sf::Event &getEvent();

        void setTexture(std::string idTexture, std::string namePath);
        std::shared_ptr<sf::Texture> getTexture(std::string idTexture) const;
        std::map<std::string, std::shared_ptr<sf::Texture>> getAllTexture();

        void setFont(std::string idFont, std::string namePath);
        std::shared_ptr<sf::Font> getFont(std::string idFont) const;
        std::map<std::string, std::shared_ptr<sf::Font>> getAllFont();

        // void setMusic(std::string idMusic, std::string namePath);
        // std::shared_ptr<sf::Music> getMusic(std::string idMusic) const;
        // std::map<std::string, std::shared_ptr<sf::Music>> getAllMusic();

        void clear();
        void display();

    protected:
    private:
        sf::Event _event;
        std::shared_ptr<sf::RenderWindow> _window;
        std::map<std::string, std::shared_ptr<sf::Texture>> _textureList;
        std::map<std::string, std::shared_ptr<sf::Font>> _fontList;
        // std::map<std::string, std::shared_ptr<sf::Music>> _musicsList;
};

#endif /* !INITSFML_HPP_ */
