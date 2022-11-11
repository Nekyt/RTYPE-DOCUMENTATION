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
#include <deque>

namespace ECS {
class EntityManager {
public:
    EntityManager() = default;
    ~EntityManager() = default;

    Entity createEntity(EntityType t);
    void destroyEntity(Entity e);

    std::deque<Entity>& getEntities();
    std::deque<Entity> getEntityByType(EntityType type);
    Entity getEntityById(std::size_t id);

private:
    std::deque<Entity> _entities;
};
} // namespace ECS

#endif /* !ENTITYMANAGER_HPP_ */