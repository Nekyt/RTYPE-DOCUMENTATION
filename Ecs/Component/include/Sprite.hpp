/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** Sprite
*/

#ifndef _Sprite
#define _Sprite

#include "IComp.hpp"
#include "SFML/Graphics.hpp"

namespace ECS {

class Sprite : public IComp {
public:
    explicit Sprite() noexcept;
    Sprite(const Sprite& sprite) noexcept;
    explicit Sprite(Sprite&&) noexcept = delete;
    ~Sprite() noexcept override = default;

    void setSprite(sf::Sprite* sprite) noexcept;
    void setTexture(const sf::Texture& texture) noexcept;
    [[nodiscard]] sf::Sprite* getSprite() const noexcept;
    [[nodiscard]] const sf::Texture* getTexture() const noexcept;

    void setIntRect(sf::IntRect rect) noexcept;
    void setIntRect(int left, int top, int width, int height) noexcept;
    [[nodiscard]] sf::IntRect getIntRect() const noexcept;

    void setScale(int x, int y) noexcept;
    void setScale(sf::Vector2f scale) noexcept;
    [[nodiscard]] sf::Vector2f getScale() const noexcept;

    void setPosition(int x, int y) noexcept;
    void setPosition(sf::Vector2f pos) noexcept;
    [[nodiscard]] sf::Vector2f getPosition() const noexcept;

    Sprite& operator=(const Sprite&) const noexcept = delete;
    Sprite& operator=(Sprite&&) const noexcept = delete;

private:
    sf::Vector2f _scale;
    sf::Vector2f _pos;
    sf::IntRect _intRect;
    sf::Sprite* _sprite;
};

};

#endif