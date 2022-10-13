#include "../include/Speed.hpp"

/**
 * A constructor for the Speed class.
 *
 * @param speed The maximum speed of the entity.
 */
ECS::Speed::Speed(int maxSpeed) noexcept
    : _maxSpeed(maxSpeed)
    , _speed(0)
{
}

/**
 * Copy constructor for the Speed component.
 *
 * @param speed The speed of the entity.
 */
ECS::Speed::Speed(const Speed& speed) noexcept
    : _maxSpeed(speed.getMaxSpeed())
    , _speed(speed.getSpeed())
{
}

/**
 * It returns the speed of the entity.
 *
 * @return The speed of the entity.
 */
int ECS::Speed::getSpeed() const noexcept { return _speed; }

/**
 * This function returns the maximum speed of the entity.
 *
 * @return The max speed of the entity.
 */
void ECS::Speed::setMaxSpeed(int speed) noexcept { _maxSpeed = speed; }

/**
 * This function returns the maximum speed of the entity.
 *
 * @return The max speed of the entity.
 */
int ECS::Speed::getMaxSpeed() const noexcept { return _maxSpeed; }

/**
 * Sets the speed of the entity.
 *
 * @param speed The speed of the entity.
 */
void ECS::Speed::setSpeed(int speed) noexcept { _speed = speed; }

/**
 * If the speed is greater than the max speed, set the speed to the max speed,
 * otherwise add the speed to the current speed
 *
 * @param speed The speed of the entity.
 */
void ECS::Speed::addSpeed(int speed) noexcept
{
    if (_speed + speed > _maxSpeed)
        _speed = _maxSpeed;
    else
        _speed += speed;
}

/**
 * If the speed is less than zero, set the speed to zero, otherwise subtract the
 * speed
 *
 * @param speed The speed of the entity.
 */
void ECS::Speed::removeSpeed(int speed) noexcept
{
    if (_speed - speed < 0)
        _speed = 0;
    else
        _speed -= speed;
}