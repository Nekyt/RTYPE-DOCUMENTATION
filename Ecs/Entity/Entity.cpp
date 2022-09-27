/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** Entity
*/

#include "Entity.hpp"

ECS::Entity::Entity(std::size_t id) : _id(id)
{
}

std::size_t ECS::Entity::getId()
{
    return _id;
}