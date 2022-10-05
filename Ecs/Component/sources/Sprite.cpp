#include "../include/Sprite.hpp"

ECS::Sprite::Sprite(const sf::Texture &text, int sizeX, int sizeY, int posX, int posY) noexcept : _sizeX(sizeX), _sizeY(sizeY), _posX(posX), _posY(posY)
{
    _sprite->setTexture(text);
    _sprite->setTextureRect(sf::IntRect(_posX, _posY, _sizeX, _sizeY));
}

ECS::Sprite::Sprite(const ECS::Sprite &sprite) noexcept : _sizeX(sprite.getRectSizeX()), _sizeY(sprite.getRectSizeY()), _posX(sprite.getRectPosX()), _posY(sprite.getRectPosY()), _sprite(sprite.getSprite()) {}

void ECS::Sprite::setSprite(sf::Sprite *sprite) noexcept
{
    sf::IntRect rec;

    _sprite = sprite;
    rec.height = _sizeY;
    rec.width = _sizeX;
    rec.left = _posX;
    rec.top = _posY;
    _sprite->setTextureRect(rec);
}

sf::Sprite *ECS::Sprite::getSprite() const noexcept {return _sprite;}
const sf::Texture *ECS::Sprite::getTexture() const noexcept {return _sprite->getTexture();}

void ECS::Sprite::setRectPosX(int pos) noexcept
{
    sf::IntRect rec;

    _posX = pos;
    rec.height = _sizeY;
    rec.width = _sizeX;
    rec.left = _posX;
    rec.top = _posY;
    _sprite->setTextureRect(rec);
}

void ECS::Sprite::setRectPosY(int pos) noexcept
{
    sf::IntRect rec;

    _posY = pos;
    rec.height = _sizeY;
    rec.width = _sizeX;
    rec.left = _posX;
    rec.top = _posY;
    _sprite->setTextureRect(rec);
}

int ECS::Sprite::getRectPosX() const noexcept {return _posX;}
int ECS::Sprite::getRectPosY() const noexcept {return _posY;}

void ECS::Sprite::setRectSizeX(int size) noexcept
{
    sf::IntRect rec;

    _sizeX = size;
    rec.height = _sizeY;
    rec.width = _sizeX;
    rec.left = _posX;
    rec.top = _posY;
    _sprite->setTextureRect(rec);
}
void ECS::Sprite::setRectSizeY(int size) noexcept
{
    sf::IntRect rec;

    _sizeY = size;
    rec.height = _sizeY;
    rec.width = _sizeX;
    rec.left = _posX;
    rec.top = _posY;
    _sprite->setTextureRect(rec);
}

int ECS::Sprite::getRectSizeX() const noexcept {return _sizeX;}
int ECS::Sprite::getRectSizeY() const noexcept {return _sizeY;}