#ifndef _TEXTURE
#define _TEXTURE

#include "IComp.hpp"
#include "SFML/Graphics.hpp"

namespace ECS {

    class Texture : public IComp {
        public:
            explicit Texture() noexcept = default;
            Texture(const Texture& bonus) noexcept = default;
            explicit Texture(Texture&&) noexcept = delete;
            ~Texture() noexcept override = default;

            void setSprite(sf::Sprite *sprite) noexcept;
            [[nodiscard]] sf::Sprite *getSprite() const noexcept;

            void setRectPos_x(int) noexcept;
            void setRectPos_y(int) noexcept;
            [[nodiscard]] int getRectPos_x() const noexcept;
            [[nodiscard]] int getRectPos_y() const noexcept;

            void setRectSize_x(int) noexcept;
            void setRectSize_y(int) noexcept;
            [[nodiscard]] int getRectSize_x() const noexcept;
            [[nodiscard]] int getRectSize_y() const noexcept;

            Texture &operator=(const Texture&) const noexcept = delete;
            Texture &operator=(Texture&&) const noexcept = delete;
        private:
            int _size_x;
            int _size_y;
            int _pos_x;
            int _pos_y;
            sf::Sprite *_sprite;
    };

};

#endif