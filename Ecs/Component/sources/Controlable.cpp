#include "../include/controlable.hpp"

ECS::Controlable::Controlable(bool cont) noexcept : _controlable(cont) {}
ECS::Controlable::Controlable(const Controlable& cont) noexcept : _controlable(cont.getControlable()){}

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