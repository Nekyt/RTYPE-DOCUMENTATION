#ifndef _BONUS
#define _BONUS

#include "IComp.hpp"

namespace ECS {

enum BonusType {SPEEDBONUS, HEALTHBONUS, DAMAGEBONUS};

class Bonus : public IComp {
public:
    explicit Bonus(BonusType type) noexcept;
    Bonus(const Bonus& bonus) noexcept;
    explicit Bonus(Bonus&&) noexcept = delete;
    ~Bonus() noexcept override = default;

    Bonus& operator=(const Bonus&) const noexcept = delete;
    Bonus& operator=(Bonus&&) const noexcept = delete;

    void setBonus(BonusType type) noexcept;
    [[nodiscard]] BonusType getBonus() const noexcept;
private:
    BonusType _type;
};

};

#endif