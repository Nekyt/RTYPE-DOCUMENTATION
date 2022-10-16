#include "../include/Damage.hpp"

/**
 * This function is a constructor for the Damage component.
 *
 * @param damage The amount of damage to be dealt.
 */
ECS::Damage::Damage(int damage) noexcept
    : _damage(damage)
{
}

/**
 * Copy constructor.
 *
 * @param damage The damage to be copied.
 */
ECS::Damage::Damage(const Damage& damage) noexcept
    : _damage(damage.getDamage())
{
}

/**
 * `getDamage()` returns the damage of the `Damage` component.
 *
 * @return The damage of the entity.
 */
int ECS::Damage::getDamage() const noexcept { return _damage; }

/**
 * Sets the damage of the entity.
 *
 * @param damage The damage to be dealt.
 */
void ECS::Damage::setDamage(int damage) noexcept { _damage = damage; }