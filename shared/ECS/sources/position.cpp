#include "../include/position.hpp"

ECS::Position::Position(int x, int y) noexcept : _x(x), _y(y) {}
ECS::Position::Position(const Position &pos) noexcept : _x(pos.getPosition_x()), _y(pos.getPosition_y()) {}

int ECS::Position::getPosition_x() const noexcept {return _x;}
int ECS::Position::getPosition_y() const noexcept {return _y;}

void ECS::Position::setPosition_x(const int x) noexcept {_x = x;}
void ECS::Position::setPosition_y(const int y) noexcept {_y = y;}