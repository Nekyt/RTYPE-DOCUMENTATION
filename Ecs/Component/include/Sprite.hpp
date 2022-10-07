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

            void setSprite(sf::Sprite *sprite) noexcept;
            void setTexture(const sf::Texture &texture) noexcept;
            [[nodiscard]] sf::Sprite *getSprite() const noexcept;
            [[nodiscard]] const sf::Texture *getTexture() const noexcept;

            void setRectPosX(int) noexcept;
            void setRectPosY(int) noexcept;
            [[nodiscard]] int getRectPosX() const noexcept;
            [[nodiscard]] int getRectPosY() const noexcept;

            void setRectSizeX(int) noexcept;
            void setRectSizeY(int) noexcept;
            [[nodiscard]] int getRectSizeX() const noexcept;
            [[nodiscard]] int getRectSizeY() const noexcept;

            Sprite &operator=(const Sprite&) const noexcept = delete;
            Sprite &operator=(Sprite&&) const noexcept = delete;
        private:
            int _sizeX;
            int _sizeY;
            int _posX;
            int _posY;
            sf::Sprite *_sprite;
    };

};

#endif