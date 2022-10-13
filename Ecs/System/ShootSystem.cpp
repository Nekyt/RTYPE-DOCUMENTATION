/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** ShootSystem
*/

#include "ShootSystem.hpp"

ECS::ShootSystem::ShootSystem(const std::shared_ptr<ComponentManager> &componentsManager, const std::shared_ptr<EntityManager> &entityManager) : System(componentsManager, entityManager)
{
}

void ECS::ShootSystem::update()
{
    const auto &entities = _entityManager->getEntities();

    for (const auto &entity : entities) {
        if (!checkIsValidEntity(entity))
            continue;
        ECS::Position *position = dynamic_cast<ECS::Position*>(_componentManager->getComponent(entity, ComponentType::POSITION));
        auto *speed = dynamic_cast<ECS::Speed*>(_componentManager->getComponent(entity, ComponentType::SPEED));
        auto *acceleration =dynamic_cast<ECS::Acceleration*>(_componentManager->getComponent(entity, ComponentType::ACCELERATION));

        auto posX = position->getPosition_x();
        auto posY = position->getPosition_x();
        position->setPosition_x(posX += acceleration->getAcceleration_x() * speed->getSpeed());
        position->setPosition_x(posY += acceleration->getAcceleration_y() * speed->getSpeed());
    }
}

bool ECS::ShootSystem::checkIsValidEntity(Entity entity)
{
    auto &components = _componentManager->getComponentList(entity);

    try
    {
        components.at(ComponentType::POSITION);
        components.at(ComponentType::SPEED);
        components.at(ComponentType::ACCELERATION);
        return true;
    }
    catch(const std::exception& e)
    {
        return false;
    }
}