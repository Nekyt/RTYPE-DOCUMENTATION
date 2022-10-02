/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** Entity
*/

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <iostream>
#include <utility>
#include "EntityManager.hpp"

#define MAX_ENTITY 2000

namespace ECS
{
    class Entity {
        public:
            Entity(std::size_t id, EntityType type);
            ~Entity() = default;

            Entity(Entity const &) = default;
            Entity(Entity &&) noexcept = default;

            Entity &operator=(Entity const &) = default;
            Entity &operator=(Entity &&) noexcept = default;

            std::size_t getId() const;
            EntityType getType() const;
        private:
            std::size_t _id;
            EntityType _type;
    };
} // namespace ECS

#endif /* !ENTITY_HPP_ */