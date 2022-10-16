/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** MoveSystem
*/

#include "MoveSystem.hpp"

/**
 * It's a constructor for the MoveSystem class
 *
 * @param componentsManager The ComponentManager that the system will use to get
 * components from.
 * @param entityManager The entity manager that the system will use to get
 * entities.
 */
ECS::MoveSystem::MoveSystem(const std::shared_ptr<ComponentManager>& componentsManager, const std::shared_ptr<EntityManager>& entityManager)
    : System(componentsManager, entityManager)
{
}

/**
 * For each entity, if the entity has a position, speed, and acceleration
 * component, then update the position based on the speed and acceleration.
 */
void ECS::MoveSystem::update()
{
    const auto& entities = _entityManager->getEntities();
    std::vector<std::pair<size_t, std::vector<ECS::ComponentType>>> enti = _clock->getEntitiesToUpdate();

    for (size_t i = 0; i < enti.size(); ++i) {
        for (const auto& entity : entities) {
            if (entity.getId() != enti[i].first)
                continue;
            if (!checkIsValidEntity(entity))
                continue;
            std::shared_ptr<ECS::Position> position = std::dynamic_pointer_cast<ECS::Position>(_componentManager->getComponent(entity, ComponentType::POSITION));
            std::shared_ptr<ECS::Speed> speed = std::dynamic_pointer_cast<ECS::Speed>(_componentManager->getComponent(entity, ComponentType::SPEED));
            std::shared_ptr<ECS::Acceleration> acceleration = std::dynamic_pointer_cast<ECS::Acceleration>(_componentManager->getComponent(entity, ComponentType::ACCELERATION));

            auto posX = position->getPosition_x();
            auto posY = position->getPosition_y();
            position->setPosition_x(posX += acceleration->getAcceleration_x() * speed->getMaxSpeed());
            position->setPosition_y(posY += acceleration->getAcceleration_y() * speed->getMaxSpeed());
        }
    }
}

void ECS::MoveSystem::setClock(std::shared_ptr<Clock> clock)
{
    _clock = clock;
}

/**
 * If the entity has a position, speed, and acceleration component, then it's a
 * valid entity
 *
 * @param entity The entity to check
 *
 * @return A boolean value.
 */
bool ECS::MoveSystem::checkIsValidEntity(Entity entity)
{
    auto& components = _componentManager->getComponentList(entity);

    try {
        components.at(ComponentType::POSITION);
        components.at(ComponentType::SPEED);
        components.at(ComponentType::ACCELERATION);
        return true;
    } catch (const std::exception& e) {
        return false;
    }
}