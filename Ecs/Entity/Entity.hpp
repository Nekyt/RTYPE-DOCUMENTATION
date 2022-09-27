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

namespace ECS
{
    class Entity {
        public:
            Entity(std::size_t id);
            ~Entity() = default;

            Entity(Entity const &) = default;
            Entity(Entity &&) noexcept = default;

            Entity &operator=(Entity const &) = default;
            Entity &operator=(Entity &&) noexcept = default;

            std::size_t getId();

        protected:
        private:
            std::size_t _id;
    };
} // namespace ECS

#endif /* !ENTITY_HPP_ */
