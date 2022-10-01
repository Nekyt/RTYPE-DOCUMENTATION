#include "IComp.hpp"

namespace ECS {

    class Weapon : public IComp {
        public:
            explicit Weapon() noexcept = default;
            Weapon(const Weapon& bonus) noexcept = default;
            explicit Weapon(Weapon&&) noexcept = delete;
            ~Weapon() noexcept override = default;

            Weapon &operator=(Weapon&&) const noexcept = delete;
            Weapon &operator=(const Weapon&) const noexcept = delete;
    };

};