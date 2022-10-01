#include "../include/controlable.hpp"

ECS::Controlable::Controlable(bool cont) noexcept : _controlable(cont) {}
ECS::Controlable::Controlable(const Controlable& cont) noexcept : _controlable(cont.getControlable()){}

bool ECS::Controlable::getControlable() const noexcept {return _controlable;}
void ECS::Controlable::changeControlable() noexcept
{
    if (_controlable)
        _controlable = false;
    else
        _controlable = true;
}