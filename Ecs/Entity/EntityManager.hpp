/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** EntityManager
*/

#ifndef ENTITYMANAGER_HPP_
#define ENTITYMANAGER_HPP_

#include <set>
#include <map>
#include <vector>
#include "Entity.hpp"

namespace ECS
{
    class EntityManager {
        public:
            EntityManager() = default;
            ~EntityManager() = default;

            Entity createEntity(EntityType t);
            void destroyEntity(Entity e);

            std::vector<Entity> &getEntities();

        private:
            std::vector<Entity> _entities;

    };
} // namespace ECS

#endif /* !ENTITYMANAGER_HPP_ */