#include "IComp.hpp"
#include <utility>

namespace ECS {
class Acceleration : public IComp {
    public:
        explicit Acceleration() noexcept;
        Acceleration(const Acceleration& acc) noexcept;
        explicit Acceleration(Acceleration&&) noexcept = delete;

        Acceleration &operator=(const Acceleration&) const noexcept = delete;
        Acceleration &operator=(Acceleration&&) const noexcept = delete;

        [[nodiscard]] int getAcceleration_x() const noexcept;
        [[nodiscard]] int getAcceleration_y() const noexcept;
        void setAcceleration_x(int x) noexcept;
        void setAcceleration_y(int y) noexcept;
        ~Acceleration() noexcept override = default;
    private:
        int _x;
        int _y;
};
};