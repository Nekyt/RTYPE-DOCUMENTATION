/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** CollisionSystem
*/

#include "CollisionSystem.hpp"

/**
 * It's a constructor for the CollisionSystem class
 *
 * @param componentsManager The ComponentManager that will be used to get the
 * components of the entities.
 * @param entityManager The entity manager that will be used to get the entities
 * that have the components that the system will use.
 */
ECS::CollisionSystem::CollisionSystem(const std::shared_ptr<ComponentManager> &componentsManager, const std::shared_ptr<EntityManager> &entityManager) : System(componentsManager, entityManager)
{
}

/**
 * If the entity is valid, check if it's colliding with another entity, and if it
 * is, remove health from the entity
 */
void ECS::CollisionSystem::update()
{
    const auto &entities = _entityManager->getEntities();

    for (const auto &entity : entities) {
        if (!checkIsValidEntity(entity))
            continue;
        auto &position = _componentManager->getComponent(entity, ComponentType::POSITION);
        auto &hitbox = _componentManager->getComponent(entity, ComponentType::HITBOX);
        auto &health = _componentManager->getComponent(entity, ComponentType::HEALTH);
        auto id = entity.getId();
        for (const auto &entity2 : entities) {
            if (!checkIsValidEntity(entity2))
                continue;
            auto id2 = entity2.getId();
            if (id == id2)
                continue;
            auto &position2 = _componentManager->getComponent(entity2, ComponentType::POSITION);
            auto &hitbox2 = _componentManager->getComponent(entity2, ComponentType::HITBOX);
            auto &health2 = _componentManager->getComponent(entity2, ComponentType::HEALTH);
            // if (hitbox.isColliding(position, hitbox2, position2) ==  true) {
            //     if ((entity.getType() == EntityType::PLAYER) && (entity2.getType() == EntityType::ENEMY))
            //         health.removeHealth(25);
            //     if ((entity.getType() == EntityType::PLAYER) && (entity2.getType() == EntityType::PROJECTILES) ||
            //         (entity.getType() == EntityType::ENEMY) && (entity2.getType() == EntityType::PROJECTILES)) {
            //         health.removeHealth(25);
            //         health2.removeHealth(health2.getHealth());
            //     }
            // }
        }
    }
}

/**
 * If the entity has a position, hitbox, and health component, then it's valid
 *
 * @param entity The entity to check
 *
 * @return A boolean value.
 */
bool ECS::CollisionSystem::checkIsValidEntity(Entity entity)
{
    auto &components = _componentManager->getComponentList(entity);

    try
    {
        components.at(ComponentType::POSITION);
        components.at(ComponentType::HITBOX);
        components.at(ComponentType::HEALTH);
        return true;
    }
    catch(const std::exception& e)
    {
        return false;
    }
}