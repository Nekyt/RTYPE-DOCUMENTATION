/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** EnemyShootSystem
*/

#include "EnemyShootSystem.hpp"

/**
 * It's the constructor for the EnemyShootSystem class.
 *
 * @param componentsManager The component manager that the system will use to
 * access components.
 * @param entityManager The entity manager that will be used to create entities.
 */
ECS::EnemyShootSystem::EnemyShootSystem(const std::shared_ptr<ComponentManager>& componentsManager, const std::shared_ptr<EntityManager>& entityManager)
    : System(componentsManager, entityManager)
{
}

/**
 * It creates a new entity of type PROJECTILE, adds a position, health, sprite and
 * speed component to it, and then sets the position of the projectile to the
 * position of the enemy
 */
void ECS::EnemyShootSystem::update()
{
    const auto& entities = _entityManager->getEntities();

    for (const auto& entity : entities) {
        if (!checkIsValidEntity(entity))
            continue;
        if (entity.getType() != ECS::EntityType::ENEMY)
            continue;
        std::shared_ptr<ECS::Position> position = std::dynamic_pointer_cast<ECS::Position>(_componentManager->getComponent(entity, ComponentType::POSITION));
        // clock pour la fréquence de tire

        short posProjectile_x = position->getPosition_x();
        short posProjectile_y = position->getPosition_y();

        ECS::Entity entityProjectile = _entityManager->createEntity(ECS::EntityType::PROJECTILES);
        _componentManager->addComponent(entityProjectile, ECS::ComponentType::POSITION, std::make_shared<ECS::Position>(posProjectile_x, posProjectile_y));
        _componentManager->addComponent(entityProjectile, ECS::ComponentType::ACCELERATION, std::make_shared<ECS::Acceleration>(-1, 0));
        _componentManager->addComponent(entityProjectile, ECS::ComponentType::HEALTH, std::make_shared<ECS::Health>(1));
        _componentManager->addComponent(entityProjectile, ECS::ComponentType::SPRITE, std::make_shared<ECS::Sprite>(*_sfml->getTexture("enemy"), sf::Vector2f(2, 2), sf::IntRect(0, 0, 1135, 345), sf::Vector2f(posProjectile_x, posProjectile_y)));
        _componentManager->addComponent(entityProjectile, ECS::ComponentType::SPEED, std::make_shared<ECS::Speed>(16));
        _componentManager->addComponent(entityProjectile, ECS::ComponentType::DAMAGE, std::make_shared<ECS::Damage>(20));
        _componentManager->addComponent(entityProjectile, ECS::ComponentType::BULLET, std::make_shared<ECS::Bullet>(false));
        _clock->addClockComponent(entityProjectile.getId(), ECS::ComponentType::BULLET, 10000);
    }
}

/**
 * It sets the sfml pointer to the one passed in
 *
 * @param sfml The InitSfml class that is used to initialize the SFML library.
 */
void ECS::EnemyShootSystem::setSfml(std::shared_ptr<InitSfml> sfml)
{
    _sfml = sfml;
}

void ECS::EnemyShootSystem::setClock(std::shared_ptr<Clock> clock)
{
    _clock = clock;
}

/**
 * If the entity has a speed, health, sprite, and position component, then it's a
 * valid entity
 *
 * @param entity The entity to check
 *
 * @return A boolean value.
 */
bool ECS::EnemyShootSystem::checkIsValidEntity(Entity entity)
{
    auto& components = _componentManager->getComponentList(entity);

    try {
        components.at(ComponentType::SPEED);
        components.at(ComponentType::HEALTH);
        components.at(ComponentType::SPRITE);
        components.at(ComponentType::POSITION);
        return true;
    } catch (const std::exception& e) {
        return false;
    }
}