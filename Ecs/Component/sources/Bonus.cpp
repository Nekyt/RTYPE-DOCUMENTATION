/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** Bonus
*/

#include "../include/Bonus.hpp"

/**
 * It's a constructor that takes a BonusType and sets the _type member variable to
 * the value of the parameter
 * 
 * @param type The type of the bonus.
 */
ECS::Bonus::Bonus(BonusType type) noexcept : _type(type)
{
}

/**
 * It's a copy constructor
 * 
 * @param bonus The bonus to copy.
 */
ECS::Bonus::Bonus(const Bonus& bonus) noexcept : _type(bonus.getBonus())
{
}

/**
 * It sets the type of the bonus
 * 
 * @param type The type of bonus.
 */
void ECS::Bonus::setBonus(BonusType type) noexcept
{
    _type = type;
}


/**
 * This function returns the type of bonus.
 * 
 * @return The type of bonus.
 */
ECS::BonusType ECS::Bonus::getBonus() const noexcept { return _type; }