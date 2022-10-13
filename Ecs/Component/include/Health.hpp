#ifndef _HEALTH
#define _HEALTH

#include "IComp.hpp"

namespace ECS {

class Health : public IComp {
public:
    explicit Health(int life) noexcept;
    Health(const Health& health) noexcept;
    explicit Health(Health&&) noexcept = delete;
    ~Health() noexcept override = default;

    Health& operator=(const Health&) const noexcept = delete;
    Health& operator=(Health&&) const noexcept = delete;

    [[nodiscard]] int getHealth() const noexcept;
    [[nodiscard]] int getMaxHealth() const noexcept;
    void addHealth(int const healthToAdd) noexcept;
    void removeHealth(int const healthToRemove) noexcept;
    void setHealth(int const healthToSet) noexcept;

private:
    int _maxHealth;
    int _health;
};

};

#endif