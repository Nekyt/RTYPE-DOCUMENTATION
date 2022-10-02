#include "../include/size.hpp"

ECS::Size::Size(unsigned short x, unsigned short y) noexcept : _x(x), _y(y) {}
ECS::Size::Size(const Size &size) noexcept : _x(size.getSize_x()), _y(size.getSize_y()) {}

unsigned short ECS::Size::getSize_x() const noexcept {return _x;}
unsigned short ECS::Size::getSize_y() const noexcept {return _y;}
void ECS::Size::setSize_x(const unsigned short x) noexcept {_x = x;}
void ECS::Size::setSize_y(const unsigned short y) noexcept {_y = y;}