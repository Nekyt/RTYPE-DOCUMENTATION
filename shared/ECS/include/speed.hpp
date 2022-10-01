#include "IComp.hpp"

namespace ECS {

class Speed : public IComp {
    public:
        explicit Speed(int speed) noexcept;
        Speed(const Speed& speed) noexcept;
        explicit Speed(Speed&&) noexcept = delete;
        ~Speed() noexcept override = default;

        Speed &operator=(const Speed&) const noexcept = delete;
        Speed &operator=(Speed&&) const noexcept = delete;

        [[nodiscard]]int getSpeed() const noexcept;
        [[nodiscard]]int getMaxSpeed() const noexcept;
        void addSpeed(int const speedToAdd) noexcept;
        void removeSpeed(int const speedToRemove) noexcept;
        void setSpeed(int const speedToSet) noexcept;
        void setMaxSpeed(int const speedToSet) noexcept;

    private:
        int _maxSpeed;
        int _speed;
};

};