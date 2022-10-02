#ifndef _POSITION
#define _POSITION

#include "IComp.hpp"

namespace ECS {

class Position : public IComp {
    public:
        explicit Position(unsigned short x, unsigned short y) noexcept;
        Position(const Position& pos) noexcept;
        explicit Position(Position&&) noexcept = delete;
        ~Position() noexcept override = default;

        Position &operator=(const Position&) const noexcept = delete;
        Position &operator=(Position&&) const noexcept = delete;

        [[nodiscard]] unsigned short getPosition_x() const noexcept;
        [[nodiscard]] unsigned short getPosition_y() const noexcept;
        void setPosition_x(unsigned short x) noexcept;
        void setPosition_y(unsigned short y) noexcept;

    private:
        unsigned short _x;
        unsigned short _y;
};
};

#endif