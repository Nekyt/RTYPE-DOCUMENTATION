#include "../include/acceleration.hpp"

ECS::Acceleration::Acceleration() noexcept : _x(0), _y(0) {}
ECS::Acceleration::Acceleration(const Acceleration& acc) noexcept : _x(acc.getAcceleration_x()), _y(acc.getAcceleration_y()){}

int ECS::Acceleration::getAcceleration_x() const noexcept {return _x;}
int ECS::Acceleration::getAcceleration_y() const noexcept {return _y;}

void ECS::Acceleration::setAcceleration_x(int x) noexcept {_x = x;}
void ECS::Acceleration::setAcceleration_y(int y) noexcept {_y = y;}