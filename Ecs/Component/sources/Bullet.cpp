/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** Bullet
*/

#include "../include/Bullet.hpp"


/**
 * This function is a constructor for the Bullet class
 * 
 * @param isFriend Whether the bullet is friendly or not.
 */
ECS::Bullet::Bullet(bool isFriend) noexcept : _isFriend(isFriend)
{
}

/**
 * This function sets the bullet to be friendly or not.
 * 
 * @param isFriend Whether the bullet is friendly or not.
 */
void ECS::Bullet::setBullet(const bool& isFriend) noexcept
{
    _isFriend = isFriend;
}

/**
 * It returns the value of the private variable _isFriend.
 * 
 * @return A boolean value.
 */
bool ECS::Bullet::getBullet() const noexcept { return _isFriend; }