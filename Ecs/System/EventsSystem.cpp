/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** EventsSystem
*/

#include "EventsSystem.hpp"

ECS::EventsSystem::EventsSystem(const std::shared_ptr<ComponentManager>& componentsManager, const std::shared_ptr<EntityManager>& entityManager)
    : System(componentsManager, entityManager)
{
}

void ECS::EventsSystem::update()
{
    const auto& entities = _entityManager->getEntities();

    for (const auto& entity : entities) {
        if (entity.getType() != ECS::EntityType::PLAYER)
            continue;
        if (!checkIsValidEntity(entity))
            continue;
        for (auto event : _currentEvents) {
            if (event.second == Button::Space && event.first == entity)
                shoot(entity);
            else if (event.first == entity)
                modifyAcceleration(entity, event);
        }
    }
}

void ECS::EventsSystem::setEvents(Entity entity, Button event)
{
    _currentEvents[entity] = event;
}

void ECS::EventsSystem::modifyAcceleration(Entity entity, std::vector<Button> event)
{
    auto* speed = dynamic_cast<ECS::Speed*>(_componentManager->getComponent(entity, ComponentType::SPEED));
    auto* acceleration = dynamic_cast<ECS::Acceleration*>(_componentManager->getComponent(entity, ComponentType::ACCELERATION));

    switch (event.second) {
    case Button::Right:
        acceleration->setAcceleration_x(1);
        acceleration->setAcceleration_y(0);
        speed->setMaxSpeed(12);
        break;
    case Button::Left:
        acceleration->setAcceleration_x(-1);
        acceleration->setAcceleration_y(0);
        speed->setMaxSpeed(12);
        break;
    case Button::Down:
        acceleration->setAcceleration_x(0);
        acceleration->setAcceleration_y(1);
        speed->setMaxSpeed(12);
        break;
    case Button::Up:
        acceleration->setAcceleration_x(0);
        acceleration->setAcceleration_y(-1);
        speed->setMaxSpeed(12);
        break;
    default:
        break;
    }
}

void ECS::EventsSystem::shoot(Entity entity)
{
    auto* position = dynamic_cast<ECS::Position*>(_componentManager->getComponent(entity, ComponentType::POSITION));
    // clock pour la fréquence de tire

    short posProjectile_x = position->getPosition_x();
    short posProjectile_y = position->getPosition_y();

    ECS::Entity entityProjectile = _entityManager->createEntity(ECS::EntityType::PROJECTILES);
    _componentManager.addComponent(entityProjectile, ECS::ComponentType::POSITION);
    //_componentManager.addComponent(entityProjectile, ECS::ComponentType::BULLET); isFriend = true
    // reset la clock pour la fréquence de tire aussi non on va pas s'en sortir
}

void ECS::EventsSystem::clearEvents()
{
    for (auto& i : _currentEvents)
        i.second.clear();
}

bool ECS::EventsSystem::checkIsValidEntity(Entity entity)
{
    auto& components = _componentManager->getComponentList(entity);

    try {
        components.at(ComponentType::SPEED);
        components.at(ComponentType::ACCELERATION);
        components.at(ComponentType::POSITION);
        return true;
    } catch (const std::exception& e) {
        return false;
    }
}