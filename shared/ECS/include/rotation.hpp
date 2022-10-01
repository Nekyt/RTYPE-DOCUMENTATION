#include "IComp.hpp"

namespace ECS {

class Rotation : public IComp {
    public:
        explicit Rotation(short rotation) noexcept;
        Rotation(const Rotation& rotation) noexcept;
        explicit Rotation(Rotation&&) noexcept = delete;
        ~Rotation() noexcept override = default;

        Rotation &operator=(const Rotation&) const noexcept = delete;
        Rotation &operator=(Rotation&&) const noexcept = delete;

        [[nodiscard]] short getRotation() const noexcept;
        void setRotation(short rotation) noexcept;
    private:
        short _rotation;
};

};