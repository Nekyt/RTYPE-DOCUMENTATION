#include "../include/Text.hpp"

ECS::Text::Text(std::string &text, int size, sf::Font &font) noexcept : _sentence(text), _size(size), _font(font)
{
    _text.setFont(_font);
    _text.setCharacterSize(_size);
    _text.setString(_sentence);
}

ECS::Text::Text(const Text& text) noexcept : _sentence(text.getSentence()), _size(text.getTextSize()), _font(text.getFont())
{
    _text.setFont(_font);
    _text.setCharacterSize(_size);
    _text.setString(_sentence);
}

sf::Text &ECS::Text::getText() noexcept {return _text;}
sf::Font ECS::Text::getFont() const noexcept {return _font;}
std::string ECS::Text::getSentence() const noexcept {return _sentence;}
int ECS::Text::getTextSize() const noexcept {return _size;}

void ECS::Text::setSizeText(int size) noexcept
{
    _size = size;
    _text.setCharacterSize(_size);
}

void ECS::Text::setSentence(const std::string &sentence) noexcept
{
    _sentence = sentence;
    _text.setString(_sentence);
}