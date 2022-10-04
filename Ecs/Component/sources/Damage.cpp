#include "../include/Damage.hpp"

ECS::Damage::Damage(int damage) noexcept : _damage(damage) {}
ECS::Damage::Damage(const Damage& damage) noexcept : _damage(damage.getDamage()){}

int ECS::Damage::getDamage() const noexcept {return _damage;}

void ECS::Damage::setDamage(int damage) noexcept {_damage = damage;}