#include "../include/rotation.hpp"

ECS::Rotation::Rotation(short rotation) noexcept : _rotation(rotation) {}
ECS::Rotation::Rotation(const Rotation& rotation) noexcept : _rotation(rotation.getRotation()){}

short ECS::Rotation::getRotation() const noexcept {return _rotation;}
void ECS::Rotation::setRotation(short rotation) noexcept {_rotation = rotation;}