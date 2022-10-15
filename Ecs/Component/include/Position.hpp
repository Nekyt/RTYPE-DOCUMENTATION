#ifndef _POSITION
#define _POSITION

#include "IComp.hpp"

namespace ECS {

class Position : public IComp {
public:
    explicit Position(short x, short y) noexcept;
    Position(const Position& pos) noexcept;
    explicit Position(Position&&) noexcept = delete;
    ~Position() noexcept override = default;

    Position& operator=(const Position&) const noexcept = delete;
    Position& operator=(Position&&) const noexcept = delete;

    [[nodiscard]] short getPosition_x() const noexcept;
    [[nodiscard]] short getPosition_y() const noexcept;
    void setPosition_x(short x) noexcept;
    void setPosition_y(short y) noexcept;

private:
    short _x;
    short _y;
};
};

#endif