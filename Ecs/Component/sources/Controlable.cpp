#include "../include/Controlable.hpp"

/**
 * This function is a constructor for the Controlable class. It takes a boolean as
 * a parameter and sets the _controlable variable to that boolean
 * 
 * @param cont Whether or not the entity is controlable.
 */
ECS::Controlable::Controlable(bool cont) noexcept : _controlable(cont) {}

/**
 * Copy constructor for the Controlable class.
 * 
 * @param cont The Controlable object to copy.
 */
ECS::Controlable::Controlable(const Controlable& cont) noexcept : _controlable(cont.getControlable()){}

/**
 * It returns the value of the private variable _controlable.
 * 
 * @return A boolean value.
 */
bool ECS::Controlable::getControlable() const noexcept {return _controlable;}

/**
 * If the entity is controlable, it becomes not controlable, and if it's not
 * controlable, it becomes controlable
 */
void ECS::Controlable::changeControlable() noexcept
{
    if (_controlable)
        _controlable = false;
    else
        _controlable = true;
}