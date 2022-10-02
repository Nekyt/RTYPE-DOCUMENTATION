#include "../include/Rotate.hpp"

ECS::Rotate::Rotate(short rotate) noexcept : _rotate(rotate) {}
ECS::Rotate::Rotate(const Rotate& rotate) noexcept : _rotate(rotate.getRotate()){}

short ECS::Rotate::getRotate() const noexcept {return _rotate;}
void ECS::Rotate::setRotate(short rotate) noexcept {_rotate = rotate;}