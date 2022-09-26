#include "IComp.hpp"

namespace ECS {

class Damage : public IComp {
    public:
        explicit Damage(int damage) noexcept;
        Damage(const Damage& damage) noexcept;
        explicit Damage(Damage&&) noexcept = delete;
        ~Damage() noexcept override = default;

        Damage &operator=(const Damage&) const noexcept = delete;
        Damage &operator=(Damage&&) const noexcept = delete;

        [[nodiscard]] int getDamage() const noexcept;
        void setDamage(int damage) noexcept;
    private:
        int _damage;
};

};