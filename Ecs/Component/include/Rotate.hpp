#ifndef _ROTATE
#define _ROTATE

#include "IComp.hpp"

namespace ECS {

class Rotate : public IComp {
public:
    explicit Rotate(short rotate) noexcept;
    Rotate(const Rotate& rotate) noexcept;
    explicit Rotate(Rotate&&) noexcept = delete;
    ~Rotate() noexcept override = default;

    Rotate& operator=(const Rotate&) const noexcept = delete;
    Rotate& operator=(Rotate&&) const noexcept = delete;

    [[nodiscard]] short getRotate() const noexcept;
    void setRotate(short rotate) noexcept;

private:
    short _rotate;
};

};

#endif