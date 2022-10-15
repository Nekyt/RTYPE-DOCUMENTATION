#include "../include/Position.hpp"

/**
 * Constructor for the Position component, which takes two short integers
 * as parameters and assigns them to the _x and _y member variables.
 *
 * @param x The x coordinate of the position.
 * @param y The y coordinate of the position.
 */
ECS::Position::Position(short x, short y) noexcept
    : _x(x)
    , _y(y)
{
}

/**
 * Copy constructor
 *
 * @param pos The position to copy.
 */
ECS::Position::Position(const Position& pos) noexcept
    : _x(pos.getPosition_x())
    , _y(pos.getPosition_y())
{
}

/**
 * It returns the value of the private variable _x.
 *
 * @return A constant reference to the private member variable _x.
 */
short ECS::Position::getPosition_x() const noexcept { return _x; }

/**
 * It returns the value of the private variable _y.
 *
 * @return A reference to the position_x variable.
 */
short ECS::Position::getPosition_y() const noexcept { return _y; }

/**
 * Sets the x position of the entity.
 *
 * @param x The x position of the entity.
 */
void ECS::Position::setPosition_x(const short x) noexcept { _x = x; }

/**
 * This function sets the y position of the entity.
 *
 * @param y The y position of the entity.
 */
void ECS::Position::setPosition_y(const short y) noexcept { _y = y; }