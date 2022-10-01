#include "../include/hitbox.hpp"

ECS::Hitbox::Hitbox(unsigned short sizex, unsigned short sizey) noexcept : _sizex(sizex), _sizey(sizey) {}
ECS::Hitbox::Hitbox(const Hitbox &hitbox) noexcept : _sizex(hitbox.getWidth()), _sizey(hitbox.getHeight()) {}

unsigned short ECS::Hitbox::getWidth() const noexcept {return _sizex;}
unsigned short ECS::Hitbox::getHeight() const noexcept {return _sizey;}
void ECS::Hitbox::setWidth(unsigned short width) noexcept {_sizex = width;}
void ECS::Hitbox::setHeight(unsigned short height) noexcept {_sizey = height;}
bool ECS::Hitbox::isColliding(const ECS::Position &current, const ECS::Hitbox &compare, const ECS::Position &comp) const noexcept
{
    if (current.getPosition_x() >= comp.getPosition_x() && current.getPosition_x() <= comp.getPosition_x() + compare.getWidth() && current.getPosition_y() >= comp.getPosition_y() && current.getPosition_y() <= comp.getPosition_y() + compare.getHeight())
        return true;
    else if (current.getPosition_x() >= comp.getPosition_x() && current.getPosition_x() <= comp.getPosition_x() + compare.getWidth() && current.getPosition_y() + _sizey >= comp.getPosition_y() && current.getPosition_y() + _sizey <= comp.getPosition_y() + compare.getHeight())
        return true;
    else if (current.getPosition_x() + _sizex >= comp.getPosition_x() && current.getPosition_x() + _sizex <= comp.getPosition_x() + compare.getWidth() && current.getPosition_y() >= comp.getPosition_y() && current.getPosition_y() <= comp.getPosition_y() + compare.getHeight())
        return true;
    else if (current.getPosition_x() + _sizex >= comp.getPosition_x() && current.getPosition_x() + _sizex <= comp.getPosition_x() + compare.getWidth() && current.getPosition_y() + _sizey >= comp.getPosition_y() && current.getPosition_y() + _sizey <= comp.getPosition_y() + compare.getHeight())
        return true;
    return false;
}