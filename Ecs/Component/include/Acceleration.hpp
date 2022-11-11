#ifndef _ACCELERATION
#define _ACCELERATION

#include "IComp.hpp"
#include <utility>

namespace ECS {
class Acceleration : public IComp {
public:
    explicit Acceleration(float x, float y) noexcept;
    Acceleration(const Acceleration& acc) noexcept;
    explicit Acceleration(Acceleration&&) noexcept = delete;

    Acceleration& operator=(const Acceleration&) const noexcept = delete;
    Acceleration& operator=(Acceleration&&) const noexcept = delete;

    [[nodiscard]] float getAcceleration_x() const noexcept;
    [[nodiscard]] float getAcceleration_y() const noexcept;
    void setAcceleration_x(float x) noexcept;
    void setAcceleration_y(float y) noexcept;
    ~Acceleration() noexcept override = default;

private:
    float _x;
    float _y;
};
};

#endif