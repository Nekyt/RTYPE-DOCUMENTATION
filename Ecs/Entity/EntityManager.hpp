/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** EntityManager
*/

#ifndef ENTITYMANAGER_HPP_
#define ENTITYMANAGER_HPP_

#include "Entity.hpp"
#include <set>
#include <map>
#include <vector>

namespace ECS
{
    enum EntityType {PLAYER, ENEMY, PROJECTILES, OBSTACLES, GRAPHICS};

    class EntityManager {
        public:
            EntityManager();
            ~EntityManager() = default;

            Entity createEntity(EntityType t);
            void destroyEntity(Entity e);

            std::vector<Entity> &getEntities() const;

        private:
            std::vector<Entity> _entities;

    };
} // namespace ECS

#endif /* !ENTITYMANAGER_HPP_ */