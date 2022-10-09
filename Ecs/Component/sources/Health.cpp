#include "../include/Health.hpp"

/**
 * This function is a constructor for the Health component. It takes in an integer
 * and sets the max health and current health to that value.
 * 
 * @param life The amount of health the entity will have.
 */
ECS::Health::Health(int life) noexcept : _maxHealth(life), _health(life) {}

/**
 * Copy constructor for the Health class
 * 
 * @param health The health to copy.
 */
ECS::Health::Health(const Health &health) noexcept : _maxHealth(health.getHealth()), _health(health.getHealth()) {}

/**
 * This function returns the value of the private member variable _health.
 * 
 * @return The health of the entity.
 */
int ECS::Health::getHealth() const noexcept {return _health;}

/**
 * This function returns the maximum health of the entity.
 * 
 * @return The max health of the entity.
 */
int ECS::Health::getMaxHealth() const noexcept {return _maxHealth;}

/**
 * This function sets the health of the entity.
 * 
 * @param health The health of the entity.
 */
void ECS::Health::setHealth(int health) noexcept {_health = health;}

/**
 * If the health is greater than the max health, set the health to the max health,
 * otherwise add the health
 * 
 * @param health The current health of the entity.
 */
void ECS::Health::addHealth(int health) noexcept {
    if (_health + health > _maxHealth)
        _health = _maxHealth;
    else
        _health += health;
}

/**
 * If the health is less than 0, set it to 0, otherwise subtract the health
 * 
 * @param health The amount of health to add to the entity.
 */
void ECS::Health::removeHealth(int health) noexcept {
    if (_health - health < 0)
        _health = 0;
    else
        _health -= health;
}