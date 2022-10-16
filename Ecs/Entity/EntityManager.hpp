/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** EntityManager
*/

#ifndef ENTITYMANAGER_HPP_
#define ENTITYMANAGER_HPP_

#include "Entity.hpp"
#include <map>
#include <set>
#include <vector>

namespace ECS {
class EntityManager {
public:
    EntityManager() = default;
    ~EntityManager() = default;

    Entity createEntity(EntityType t);
    void destroyEntity(Entity e);

    std::vector<Entity>& getEntities();
    Entity getEntityByType(EntityType type);

private:
    std::vector<Entity> _entities;
};
} // namespace ECS

#endif /* !ENTITYMANAGER_HPP_ */