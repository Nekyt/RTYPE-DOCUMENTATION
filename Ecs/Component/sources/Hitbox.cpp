#include "../include/Hitbox.hpp"
/**
 * It sets the width of the hitbox.
 *
 * @param sizex The width of the hitbox.
 * @param sizey The height of the hitbox.
 */

ECS::Hitbox::Hitbox(unsigned short sizex, unsigned short sizey) noexcept
    : _sizex(sizex)
    , _sizey(sizey)
{
}

/**
 * Copy constructor.
 *
 * @param hitbox The hitbox to copy.
 */
ECS::Hitbox::Hitbox(const Hitbox& hitbox) noexcept
    : _sizex(hitbox.getWidth())
    , _sizey(hitbox.getHeight())
{
}

/**
 * It returns the width of the hitbox.
 *
 * @return The width of the hitbox.
 */
unsigned short ECS::Hitbox::getWidth() const noexcept { return _sizex; }

/**
 * It returns the height of the hitbox.
 *
 * @return The height of the hitbox.
 */
unsigned short ECS::Hitbox::getHeight() const noexcept { return _sizey; }

/**
 * Sets the width of the hitbox.
 *
 * @param width The width of the hitbox.
 */
void ECS::Hitbox::setWidth(unsigned short width) noexcept { _sizex = width; }

/**
 * Sets the height of the hitbox.
 *
 * @param height The height of the hitbox.
 */
void ECS::Hitbox::setHeight(unsigned short height) noexcept { _sizey = height; }

/**
 * If any of the four corners of the current hitbox are inside the other hitbox,
 * then they are colliding
 *
 * @param current The position of the current entity
 * @param compare The hitbox to compare with
 * @param comp The position of the entity you're comparing to
 *
 * @return A boolean.
 */
bool ECS::Hitbox::isColliding(const ECS::Position* current, const ECS::Hitbox* compare, const ECS::Position* comp) const noexcept
{
    if (current->getPosition_x() >= comp->getPosition_x() && current->getPosition_x() <= comp->getPosition_x() + compare->getWidth() && current->getPosition_y() >= comp->getPosition_y() && current->getPosition_y() <= comp->getPosition_y() + compare->getHeight())
        return true;
    else if (current->getPosition_x() >= comp->getPosition_x() && current->getPosition_x() <= comp->getPosition_x() + compare->getWidth() && current->getPosition_y() + _sizey >= comp->getPosition_y() && current->getPosition_y() + _sizey <= comp->getPosition_y() + compare->getHeight())
        return true;
    else if (current->getPosition_x() + _sizex >= comp->getPosition_x() && current->getPosition_x() + _sizex <= comp->getPosition_x() + compare->getWidth() && current->getPosition_y() >= comp->getPosition_y() && current->getPosition_y() <= comp->getPosition_y() + compare->getHeight())
        return true;
    else if (current->getPosition_x() + _sizex >= comp->getPosition_x() && current->getPosition_x() + _sizex <= comp->getPosition_x() + compare->getWidth() && current->getPosition_y() + _sizey >= comp->getPosition_y() && current->getPosition_y() + _sizey <= comp->getPosition_y() + compare->getHeight())
        return true;
    return false;
}