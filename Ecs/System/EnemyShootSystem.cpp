/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** EnemyShootSystem
*/

#include "EnemyShootSystem.hpp"

ECS::EnemyShootSystem::EnemyShootSystem(const std::shared_ptr<ComponentManager>& componentsManager, const std::shared_ptr<EntityManager>& entityManager)
    : System(componentsManager, entityManager)
{
}

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
        _componentManager->addComponent(entityProjectile, ECS::ComponentType::HEALTH, std::make_shared<ECS::Health>(1));
        _componentManager->addComponent(entityProjectile, ECS::ComponentType::SPRITE, std::make_shared<ECS::Sprite>(*_sfml->getTexture("enemy"), sf::Vector2f(2, 2), sf::IntRect(0, 0, 1135, 345), sf::Vector2f(posProjectile_x, posProjectile_y)));
        _componentManager->addComponent(entityProjectile, ECS::ComponentType::SPEED, std::make_shared<ECS::Speed>(16));
        //_componentManager.addComponent(entityProjectile, ECS::ComponentType::BULLET); isFriend = false
        // reset la clock pour la fréquence de tire aussi non on va pas s'en sortir
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