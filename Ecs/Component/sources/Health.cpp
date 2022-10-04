#include "../include/Health.hpp"

ECS::Health::Health(int life) noexcept : _maxHealth(life), _health(life) {}
ECS::Health::Health(const Health &health) noexcept : _maxHealth(health.getHealth()), _health(health.getHealth()) {}

int ECS::Health::getHealth() const noexcept {return _health;}
int ECS::Health::getMaxHealth() const noexcept {return _maxHealth;}

void ECS::Health::setHealth(int health) noexcept {_health = health;}
void ECS::Health::addHealth(int health) noexcept {
    if (_health + health > _maxHealth)
        _health = _maxHealth;
    else
        _health += health;
}
void ECS::Health::removeHealth(int health) noexcept {
    if (_health - health < 0)
        _health = 0;
    else
        _health -= health;
}