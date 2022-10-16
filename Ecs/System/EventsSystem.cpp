/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** EventsSystem
*/

#include "EventsSystem.hpp"

/**
 * It's a constructor for the EventsSystem class
 * 
 * @param componentsManager The ComponentManager that will be used to get the
 * components of the entities.
 * @param entityManager The entity manager that will be used to create entities.
 */
ECS::EventsSystem::EventsSystem(const std::shared_ptr<ComponentManager>& componentsManager, const std::shared_ptr<EntityManager>& entityManager)
    : System(componentsManager, entityManager)
{
}

/**
 * It checks if the entity is a player, if it's valid, and if it is, it checks if
 * the player has pressed the space key, and if so, it shoots a bullet. If the
 * player has pressed any other key, it modifies the acceleration of the player
 */
void ECS::EventsSystem::update()
{
    const auto& entities = _entityManager->getEntities();

    for (const auto& entity : entities) {
        if (entity.getType() != ECS::EntityType::PLAYER)
            continue;
        if (!checkIsValidEntity(entity))
            continue;
        for (auto& events : _currentEvents) {
            for (auto& event : events.second) {
                if (event == Button::Space && events.first == entity.getId())
                    shoot(entity);
                else if (events.first == entity.getId())
                    modifyAcceleration(entity, event);
            }
        }
    }
}

/**
 * It sets the sfml pointer to the one passed in
 *
 * @param sfml The InitSfml class that is used to initialize the SFML library.
 */
void ECS::EventsSystem::setSfml(std::shared_ptr<InitSfml> sfml)
{
    _sfml = sfml;
}

/**
 * It adds a button event to the entity's event list
 * 
 * @param entity The entity that the event is being set for.
 * @param event The event that is being set.
 */
void ECS::EventsSystem::setEvents(Entity& entity, Button& event)
{
    _currentEvents.at(entity.getId()).push_back(event);
}

/**
 * It modifies the acceleration of an entity based on the event that was triggered
 * 
 * @param entity The entity that will be modified.
 * @param event The event that was triggered.
 */
void ECS::EventsSystem::modifyAcceleration(Entity entity, Button event)
{
    std::shared_ptr<ECS::Speed> speed = std::dynamic_pointer_cast<ECS::Speed>(_componentManager->getComponent(entity, ComponentType::SPEED));
    std::shared_ptr<ECS::Acceleration> acceleration = std::dynamic_pointer_cast<ECS::Acceleration>(_componentManager->getComponent(entity, ComponentType::ACCELERATION));

    switch (event) {
    case Button::Right:
        acceleration->setAcceleration_x(1);
        acceleration->setAcceleration_y(0);
        speed->setSpeed(12);
        break;
    case Button::Left:
        acceleration->setAcceleration_x(-1);
        acceleration->setAcceleration_y(0);
        speed->setSpeed(12);
        break;
    case Button::Down:
        acceleration->setAcceleration_x(0);
        acceleration->setAcceleration_y(1);
        speed->setSpeed(12);
        break;
    case Button::Up:
        acceleration->setAcceleration_x(0);
        acceleration->setAcceleration_y(-1);
        speed->setSpeed(12);
        break;
    default:
        break;
    }
}

/**
 * It creates a new entity, adds a position, health, sprite, and speed component to
 * it, and then sets the sprite's position to the player's position
 * 
 * @param entity the entity that is shooting
 */
void ECS::EventsSystem::shoot(Entity entity)
{
    std::shared_ptr<ECS::Position> position = std::dynamic_pointer_cast<ECS::Position>(_componentManager->getComponent(entity, ComponentType::POSITION));
    // clock pour la fréquence de tire

    short posProjectile_x = position->getPosition_x();
    short posProjectile_y = position->getPosition_y();

    ECS::Entity entityProjectile = _entityManager->createEntity(ECS::EntityType::PROJECTILES);
    _componentManager->addComponent(entityProjectile, ECS::ComponentType::POSITION, std::make_shared<ECS::Position>(posProjectile_x, posProjectile_y));
    _componentManager->addComponent(entityProjectile, ECS::ComponentType::HEALTH, std::make_shared<ECS::Health>(1));
    _componentManager->addComponent(entityProjectile, ECS::ComponentType::SPRITE, std::make_shared<ECS::Sprite>(*_sfml->getTexture("player"), sf::Vector2f(2, 2), sf::IntRect(0, 0, 1135, 345), sf::Vector2f(posProjectile_x, posProjectile_y)));
    _componentManager->addComponent(entityProjectile, ECS::ComponentType::SPEED, std::make_shared<ECS::Speed>(16));
    //_componentManager.addComponent(entityProjectile, ECS::ComponentType::BULLET); isFriend = true
    // reset la clock pour la fréquence de tire aussi non on va pas s'en sortir
}

/**
 * It clears all the events in the current events map.
 */
void ECS::EventsSystem::clearEvents()
{
    for (auto& i : _currentEvents)
        i.second.clear();
}

/**
 * If the entity has a speed, health, sprite, and position component, then it's
 * valid
 * 
 * @param entity The entity to check
 * 
 * @return A boolean value.
 */
bool ECS::EventsSystem::checkIsValidEntity(Entity entity)
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