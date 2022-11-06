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
ECS::CollisionSystem::CollisionSystem(const std::shared_ptr<ComponentManager>& componentsManager, const std::shared_ptr<EntityManager>& entityManager)
    : System(componentsManager, entityManager)
{
}

/**
 * If the entity is valid, check if it's colliding with another entity, and if it
 * is, remove health from the entity
 */
void ECS::CollisionSystem::update()
{
    const auto& entities = _entityManager->getEntities();

    for (const auto& entity : entities) {
        if (!checkIsValidEntity(entity))
            continue;
        std::shared_ptr<ECS::Position> position = std::dynamic_pointer_cast<ECS::Position>(_componentManager->getComponent(entity, ComponentType::POSITION));
        std::shared_ptr<ECS::Hitbox> hitbox = std::dynamic_pointer_cast<ECS::Hitbox>(_componentManager->getComponent(entity, ComponentType::HITBOX));
        std::shared_ptr<ECS::Health> health = std::dynamic_pointer_cast<ECS::Health>(_componentManager->getComponent(entity, ComponentType::HEALTH));
        for (const auto& entity2 : entities) {
            if (!checkIsValidEntity(entity2))
                continue;
            if (entity.getId() == entity2.getId())
                continue;
            std::shared_ptr<ECS::Position> position2 = std::dynamic_pointer_cast<ECS::Position>(_componentManager->getComponent(entity, ComponentType::POSITION));
            std::shared_ptr<ECS::Hitbox> hitbox2 = std::dynamic_pointer_cast<ECS::Hitbox>(_componentManager->getComponent(entity, ComponentType::HITBOX));
            std::shared_ptr<ECS::Health> health2 = std::dynamic_pointer_cast<ECS::Health>(_componentManager->getComponent(entity, ComponentType::HEALTH));
            std::shared_ptr<ECS::Damage> damage2 = std::dynamic_pointer_cast<ECS::Damage>(_componentManager->getComponent(entity, ComponentType::DAMAGE));
            if (hitbox->isColliding(position, hitbox2, position2) == true) {
                if ((entity.getType() == EntityType::PLAYER) && (entity2.getType() == EntityType::ENEMY))
                    health->removeHealth(damage2->getDamage());
                if ((entity.getType() == EntityType::PLAYER && entity2.getType() == EntityType::PROJECTILES) || (entity.getType() == EntityType::ENEMY && entity2.getType() == EntityType::PROJECTILES)) {
                    health->removeHealth(damage2->getDamage());
                    health2->removeHealth(health2->getHealth());
                }
                if ((entity.getType() == EntityType::PLAYER) && (entity2.getType() == EntityType::BONUSENTITY))
                    bonusCollisionManagement(entity, entity2);
            }
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
    auto& components = _componentManager->getComponentList(entity);

    try {
        components.at(ComponentType::POSITION);
        components.at(ComponentType::HITBOX);
        components.at(ComponentType::HEALTH);
        components.at(ComponentType::DAMAGE);
        return true;
    } catch (const std::exception& e) {
        return false;
    }
}

void ECS::CollisionSystem::bonusCollisionManagement(Entity entityPlayer, Entity entityBonus)
{
    std::shared_ptr<ECS::Bonus> bonus = std::dynamic_pointer_cast<ECS::Bonus>(_componentManager->getComponent(entityBonus, ComponentType::BONUS));
    if (bonus->getBonus() == ECS::BonusType::HEALTHBONUS) {
        std::shared_ptr<ECS::Health> health = std::dynamic_pointer_cast<ECS::Health>(_componentManager->getComponent(entityPlayer, ComponentType::HEALTH));
        health->addHealth(25);
    } else if (bonus->getBonus() == ECS::BonusType::DAMAGEBONUS) {
        std::shared_ptr<ECS::Damage> damage = std::dynamic_pointer_cast<ECS::Damage>(_componentManager->getComponent(entityPlayer, ComponentType::DAMAGE));
        damage->setDamage(20);
    } else if (bonus->getBonus() == ECS::BonusType::SPEEDBONUS) {
        std::shared_ptr<ECS::Speed> speed = std::dynamic_pointer_cast<ECS::Speed>(_componentManager->getComponent(entityPlayer, ComponentType::SPEED));
        speed->addSpeed(6);
    }
}