#include "../include/Rotate.hpp"

/**
 * A constructor for the Rotate class.
 * 
 * @param rotate The amount of degrees to rotate the image.
 */
ECS::Rotate::Rotate(short rotate) noexcept : _rotate(rotate) {}

/**
 * Copy constructor for the Rotate class.
 * 
 * @param rotate The angle of rotation in degrees.
 */
ECS::Rotate::Rotate(const Rotate& rotate) noexcept : _rotate(rotate.getRotate()){}

/**
 * It returns the value of the private variable _rotate.
 * 
 * @return The rotate value.
 */
short ECS::Rotate::getRotate() const noexcept {return _rotate;}

void ECS::Rotate::setRotate(short rotate) noexcept {_rotate = rotate;}