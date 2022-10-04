#ifndef _HITBOX
#define _HITBOX

#include "IComp.hpp"
#include "Position.hpp"

namespace ECS {

class Hitbox : public IComp {
    public:
        explicit Hitbox(unsigned short sizex, unsigned short sizey) noexcept;
        Hitbox(const Hitbox& hitbox) noexcept;
        explicit Hitbox(Hitbox&&) noexcept = delete;
        ~Hitbox() noexcept override = default;

        Hitbox &operator=(const Hitbox&) const noexcept = delete;
        Hitbox &operator=(Hitbox&&) const noexcept = delete;

        [[nodiscard]] bool isColliding(const ECS::Position &current, const ECS::Hitbox &compare, const ECS::Position &comp) const noexcept;
        [[nodiscard]] unsigned short getWidth() const noexcept;
        [[nodiscard]] unsigned short getHeight() const noexcept;
        void setWidth(unsigned short width) noexcept;
        void setHeight(unsigned short height) noexcept;

    private:
        unsigned short _sizex;
        unsigned short _sizey;
};
};

#endif