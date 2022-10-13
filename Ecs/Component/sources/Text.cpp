/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** Text
*/

#include "../include/Text.hpp"

ECS::Text::Text(sf::Font& font, const std::string& sentence, int size, sf::Vector2f pos) noexcept
    : _sentence(sentence)
    , _size(size)
    , _font(font)
    , _pos(pos)
{
    _text.setFont(_font);
    _text.setCharacterSize(_size);
    _text.setString(_sentence);
    _text.setPosition(_pos);
}

/**
 * It's a copy constructor
 *
 * @param text The text to copy
 */
ECS::Text::Text(const Text& text) noexcept
    : _sentence(text.getSentence())
    , _size(text.getTextSize())
    , _font(text.getFont())
{
    _text.setFont(_font);
    _text.setCharacterSize(_size);
    _text.setString(_sentence);
}

/**
 * It returns the text object.
 *
 * @return A reference to the text object.
 */
sf::Text& ECS::Text::getText() noexcept { return _text; }

/**
 * Returns the font of the text.
 *
 * @return A reference to the font.
 */
sf::Font ECS::Text::getFont() const noexcept { return _font; }

/**
 * It returns the sentence.
 *
 * @return The sentence.
 */
std::string ECS::Text::getSentence() const noexcept { return _sentence; }

/**
 * It returns the size of the text.
 *
 * @return The text size.
 */
int ECS::Text::getTextSize() const noexcept { return _size; }

/**
 * It sets the font of the text object
 *
 * @param font The font to use for the text.
 */
void ECS::Text::setFont(sf::Font& font) noexcept
{
    _font = font;
    _text.setFont(_font);
}

/**
 * It sets the size of the text
 *
 * @param size The size of the text.
 */
void ECS::Text::setSizeText(int size) noexcept
{
    _size = size;
    _text.setCharacterSize(_size);
}

/**
 * It sets the sentence of the text
 *
 * @param sentence The string to be displayed.
 */
void ECS::Text::setSentence(const std::string& sentence) noexcept
{
    _sentence = sentence;
    _text.setString(_sentence);
}

/**
 * It sets the position of the text object
 *
 * @param x The x position of the text.
 * @param y The y position of the text.
 */
void ECS::Text::setPosition(int x, int y) noexcept
{
    _pos.x = x;
    _pos.y = y;
    _text.setPosition(_pos.x, _pos.y);
}

/**
 * It sets the position of the text object
 *
 * @param pos The position of the text.
 */
void ECS::Text::setPosition(sf::Vector2f pos) noexcept
{
    _pos = pos;
    _text.setPosition(_pos.x, _pos.y);
}

/**
 * Returns the position of the text.
 *
 * @return The position of the text.
 */
sf::Vector2f ECS::Text::getPosition() const noexcept { return _pos; }
