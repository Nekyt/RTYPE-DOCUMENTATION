/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** Entity
*/

#include "Entity.hpp"

ECS::Entity::Entity(std::size_t id, ECS::EntityType type) : _id(id), _type(type) {}

std::size_t ECS::Entity::getId() const {return _id;}
ECS::EntityType ECS::Entity::getType() const {return _type;}