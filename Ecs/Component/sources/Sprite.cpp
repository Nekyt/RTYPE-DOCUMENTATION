/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** Sprite
*/

#include "../include/Sprite.hpp"

/**
 * ECS::Sprite::Sprite() noexcept {}
 */
ECS::Sprite::Sprite() noexcept { }

/**
 * Copy constructor for the Sprite class.
 *
 * @param sprite The sprite to copy
 */
ECS::Sprite::Sprite(const ECS::Sprite& sprite) noexcept
    : _intRect(sprite.getIntRect())
    , _scale(sprite.getScale())
    , _sprite(sprite.getSprite())
{
}

/**
 * Sets the sprite to the given sprite.
 *
 * @param sprite The sprite to be set.
 */
void ECS::Sprite::setSprite(sf::Sprite* sprite) noexcept
{
    _sprite = sprite;
}

/**
 * Sets the texture of the sprite
 *
 * @param text The texture to use for the sprite.
 */
void ECS::Sprite::setTexture(const sf::Texture& text) noexcept
{
    _sprite->setTexture(text);
}

/**
 * Returns a pointer to the sprite.
 *
 * @return A pointer to the sprite.
 */
sf::Sprite* ECS::Sprite::getSprite() const noexcept { return _sprite; }

/**
 * Returns a pointer to the texture of the sprite.
 *
 * @return A pointer to the texture of the sprite.
 */
const sf::Texture* ECS::Sprite::getTexture() const noexcept { return _sprite->getTexture(); }

/**
 * Sets the sprite's texture rectangle to the given rectangle
 *
 * @param rec The new IntRect to set the sprite to.
 */
void ECS::Sprite::setIntRect(sf::IntRect rec) noexcept
{
    _intRect = rec;
    _sprite->setTextureRect(_intRect);
}

/**
 * `void ECS::Sprite::setIntRect(int left, int top, int width, int height)
 * noexcept`
 *
 * The function takes four integers as parameters and returns nothing
 *
 * @param left The x-coordinate of the top-left corner of the rectangle.
 * @param top The top position of the rectangle.
 * @param width The width of the texture in pixels.
 * @param height The height of the rectangle.
 */
void ECS::Sprite::setIntRect(int left, int top, int width, int height) noexcept
{
    _intRect.left = left;
    _intRect.top = top;
    _intRect.width = width;
    _intRect.height = height;
    _sprite->setTextureRect(_intRect);
}

/**
 * Returns the IntRect of the sprite.
 *
 * @return The intRect of the sprite.
 */
sf::IntRect ECS::Sprite::getIntRect() const noexcept { return _intRect; }

/**
 * Sets the scale of the sprite.
 *
 * @param x The x position of the sprite
 * @param y The y position of the sprite.
 */
void ECS::Sprite::setScale(int x, int y) noexcept
{
    _scale.x = x;
    _scale.y = y;
    _sprite->setScale(_scale.x, _scale.y);
}

/**
 * Sets the scale of the sprite
 *
 * @param scale The scale of the sprite.
 */
void ECS::Sprite::setScale(sf::Vector2f scale) noexcept
{
    _scale = scale;
    _sprite->setScale(_scale.x, _scale.y);
}

/**
 * Returns the scale of the sprite.
 *
 * @return The scale of the sprite.
 */
sf::Vector2f ECS::Sprite::getScale() const noexcept { return _scale; }

/**
 * It sets the position of the sprite
 *
 * @param x The x position of the sprite
 * @param y The y position of the sprite.
 */
void ECS::Sprite::setPosition(int x, int y) noexcept
{
    _pos.x = x;
    _pos.y = y;
    _sprite->setPosition(_pos.x, _pos.y);
}

/**
 * It sets the position of the sprite
 *
 * @param pos The position to set the sprite to.
 */
void ECS::Sprite::setPosition(sf::Vector2f pos) noexcept
{
    _pos = pos;
    _sprite->setPosition(_pos.x, _pos.y);
}

/**
 * Returns the position of the sprite.
 *
 * @return The position of the sprite.
 */
sf::Vector2f ECS::Sprite::getPosition() const noexcept { return _pos; }
