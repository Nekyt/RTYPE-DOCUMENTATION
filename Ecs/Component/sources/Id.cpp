#include "../include/Id.hpp"

/**
 * It takes an integer and assigns it to the _id member variable
 * 
 * @param id The id of the entity.
 */
ECS::ID::ID(int id) noexcept
    : _id(id)
{
}

/**
 * Copy constructor
 * 
 * @param id The ID to copy.
 */
ECS::ID::ID(const ID& id) noexcept
    : _id(id.getID())
{
}

/**
 * It returns the ID of the entity.
 * 
 * @return The ID of the entity.
 */
int ECS::ID::getID() const noexcept { return _id; }

/**
 * Sets the ID of the entity.
 * 
 * @param id The ID to set the ID to.
 */
void ECS::ID::setID(int id) noexcept { _id = id; }