#include "../include/Position.hpp"

ECS::Position::Position(unsigned short x, unsigned short y) noexcept : _x(x), _y(y) {}
ECS::Position::Position(const Position &pos) noexcept : _x(pos.getPosition_x()), _y(pos.getPosition_y()) {}

unsigned short ECS::Position::getPosition_x() const noexcept {return _x;}
unsigned short ECS::Position::getPosition_y() const noexcept {return _y;}

void ECS::Position::setPosition_x(const unsigned short x) noexcept {_x = x;}
void ECS::Position::setPosition_y(const unsigned short y) noexcept {_y = y;}