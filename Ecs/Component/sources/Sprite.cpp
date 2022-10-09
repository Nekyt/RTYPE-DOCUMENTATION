/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** Sprite
*/

#include "../include/Sprite.hpp"

ECS::Sprite::Sprite() noexcept {}

ECS::Sprite::Sprite(const ECS::Sprite &sprite) noexcept : _intRect(sprite.getIntRect()), _scale(sprite.getScale()), _sprite(sprite.getSprite()) {}

void ECS::Sprite::setSprite(sf::Sprite *sprite) noexcept
{
    _sprite = sprite;
}

void ECS::Sprite::setTexture(const sf::Texture &text) noexcept
{
    _sprite->setTexture(text);
}

sf::Sprite *ECS::Sprite::getSprite() const noexcept {return _sprite;}
const sf::Texture *ECS::Sprite::getTexture() const noexcept {return _sprite->getTexture();}

void ECS::Sprite::setIntRect(sf::IntRect rec) noexcept
{
    _intRect = rec;
    _sprite->setTextureRect(_intRect);
}

void ECS::Sprite::setIntRect(int left, int top, int width, int height) noexcept
{
    _intRect.left = left;
    _intRect.top = top;
    _intRect.width = width;
    _intRect.height = height;
    _sprite->setTextureRect(_intRect);
}

sf::IntRect ECS::Sprite::getIntRect() const noexcept {return _intRect;}

void ECS::Sprite::setScale(int x, int y) noexcept
{
    _scale.x = x;
    _scale.y = y;
    _sprite->setScale(_scale.x, _scale.y);
}

void ECS::Sprite::setScale(sf::Vector2f scale) noexcept
{
    _scale = scale;
    _sprite->setScale(_scale.x, _scale.y);
}

sf::Vector2f ECS::Sprite::getScale() const noexcept {return _scale;}

void ECS::Sprite::setPosition(int x, int y) noexcept
{
    _pos.x = x;
    _pos.y = y;
    _sprite->setPosition(_pos.x, _pos.y);
}

void ECS::Sprite::setPosition(sf::Vector2f pos) noexcept
{
    _pos = pos;
    _sprite->setPosition(_pos.x, _pos.y);
}

sf::Vector2f ECS::Sprite::getPosition() const noexcept {return _pos;}
