#include "../include/Speed.hpp"

ECS::Speed::Speed(int speed) noexcept : _maxSpeed(speed), _speed(0) {}
ECS::Speed::Speed(const Speed &speed) noexcept : _maxSpeed(speed.getMaxSpeed()), _speed(speed.getSpeed()) {}

int ECS::Speed::getSpeed() const noexcept {return _speed;}
int ECS::Speed::getMaxSpeed() const noexcept {return _maxSpeed;}
void ECS::Speed::setSpeed(int speed) noexcept {_speed = speed;}
void ECS::Speed::addSpeed(int speed) noexcept {
    if (_speed + speed > _maxSpeed)
        _speed = _maxSpeed;
    else
        _speed += speed;
}
void ECS::Speed::removeSpeed(int speed) noexcept {
    if (_speed - speed < 0)
        _speed = 0;
    else
        _speed -= speed;
}