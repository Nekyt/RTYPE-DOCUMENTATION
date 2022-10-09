#include "../include/Size.hpp"

/**
 * A constructor for the Size class.
 * 
 * @param x The x-coordinate of the size.
 * @param y The y coordinate of the point.
 */
ECS::Size::Size(unsigned short x, unsigned short y) noexcept : _x(x), _y(y) {}

/**
 * Copy constructor for the Size class.
 * 
 * @param size The size to copy.
 */
ECS::Size::Size(const Size &size) noexcept : _x(size.getSize_x()), _y(size.getSize_y()) {}

/**
 * It returns the value of the private member variable _x.
 * 
 * @return The value of the private member variable _x.
 */
unsigned short ECS::Size::getSize_x() const noexcept {return _x;}

/**
 * It returns the value of the private variable _y.
 * 
 * @return A reference to the private member _x
 */
unsigned short ECS::Size::getSize_y() const noexcept {return _y;}

/**
 * Sets the size of the x axis.
 * 
 * @param x The x-coordinate of the size.
 */
void ECS::Size::setSize_x(const unsigned short x) noexcept {_x = x;}

/**
 * Sets the size's y value.
 * 
 * @param y The y-coordinate of the size.
 */
void ECS::Size::setSize_y(const unsigned short y) noexcept {_y = y;}
