/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** Entity
*/

#include "Entity.hpp"

/**
 * This function is a constructor for the Entity class.
 *
 * @param id The id of the entity.
 * @param type The type of entity.
 */
ECS::Entity::Entity(std::size_t id, ECS::EntityType type)
    : _id(id)
    , _type(type)
{
}

ECS::Entity::Entity(ECS::EntityType type)
    : _type(type)
{
}

/**
 * `std::size_t ECS::Entity::getId() const {return _id;}`
 *
 * This function returns the id of the entity
 *
 * @return The id of the entity.
 */
std::size_t ECS::Entity::getId() const { return _id; }

/**
 * Returns the type of the entity.
 *
 * @return The type of the entity.
 */
ECS::EntityType ECS::Entity::getType() const { return _type; }