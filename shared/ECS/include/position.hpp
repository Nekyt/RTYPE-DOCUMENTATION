#include "IComp.hpp"
#include <utility>

namespace ECS {

class Position : public IComp {
    public:
        explicit Position(int x, int y) noexcept;
        Position(const Position& pos) noexcept;
        explicit Position(Position&&) noexcept = delete;
        ~Position() noexcept override = default;

        Position &operator=(const Position&) const noexcept = delete;
        Position &operator=(Position&&) const noexcept = delete;

        [[nodiscard]] int getPosition_x() const noexcept;
        [[nodiscard]] int getPosition_y() const noexcept;
        void setPosition_x(int x) noexcept;
        void setPosition_y(int y) noexcept;

    private:
        int _x;
        int _y;
};
};