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
 * It gets the entities to update from the clock, then it checks if the entity has
 * the required components, and if it does, it updates the position of the entity
 */
void ECS::MoveSystem::update()
{
    const auto& entities = _entityManager->getEntities();
    std::deque<std::pair<size_t, std::deque<ECS::ComponentType>>> enti = _clock->getEntitiesToUpdate();

    for (size_t i = 0; i < enti.size(); ++i) {
        for (const auto& entity : entities) {
            if (entity.getId() != enti[i].first)
                continue;
            if (!checkIsValidEntity(entity))
                continue;
            for (size_t j = 0; j < enti[i].second.size(); ++j) {
                if (enti.at(i).second.at(j) == ECS::ComponentType::SPEED) {
                    std::shared_ptr<ECS::Speed> speedRemove = std::dynamic_pointer_cast<ECS::Speed>(_componentManager->getComponent(entity, ComponentType::SPEED));
                    speedRemove->removeSpeed(6);
                    _clock->eraseClockComponent(entity.getId(), ECS::ComponentType::SPEED);
                }
                if (enti.at(i).second.at(j) != ECS::ComponentType::POSITION)
                    continue;
            }
            if (_clock->componentUpdateNumber(i, ECS::POSITION)) {
                std::shared_ptr<ECS::Position> position = std::dynamic_pointer_cast<ECS::Position>(_componentManager->getComponent(entity, ComponentType::POSITION));
                std::shared_ptr<ECS::Speed> speed = std::dynamic_pointer_cast<ECS::Speed>(_componentManager->getComponent(entity, ComponentType::SPEED));
                std::shared_ptr<ECS::Acceleration> acceleration = std::dynamic_pointer_cast<ECS::Acceleration>(_componentManager->getComponent(entity, ComponentType::ACCELERATION));

                auto posX = position->getPosition_x();
                auto posY = position->getPosition_y();
                if (entity.getType() == ECS::EntityType::PARALLAX && ((posX += acceleration->getAcceleration_x() * speed->getMaxSpeed()) < -1920))
                    position->setPosition_x(1920);
                else if (entity.getType() == ECS::EntityType::PLAYER) {
                    if (acceleration->getAcceleration_x() != 0)
                    std::cout << "In movesystem : position before : x=" << posX << " y=" << posY << " Acceleration : x=" << acceleration->getAcceleration_x() << " y=" << acceleration->getAcceleration_y() << std::endl;
                    posX += acceleration->getAcceleration_x() * speed->getMaxSpeed();
                    posY += acceleration->getAcceleration_y() * speed->getMaxSpeed();
                    position->setPosition_x(posX);
                    position->setPosition_y(posY);
                    if (posX >= 1920 - (31 * 3))
                        position->setPosition_x(1920 - (31 * 3));
                    if (posY >= 1080 - (13 * 3))
                        position->setPosition_y(1080 - (13 * 3));
                    if (posX <= 0)
                        position->setPosition_x(0);
                    if (posY <= 0)
                        position->setPosition_y(0);
                    acceleration->setAcceleration_x(0.0f);
                    acceleration->setAcceleration_y(0.0f);
                } else {
                    position->setPosition_x(posX + acceleration->getAcceleration_x() * speed->getMaxSpeed());
                    position->setPosition_y(posY + acceleration->getAcceleration_y() * speed->getMaxSpeed());
                    acceleration->setAcceleration_x(0.0f);
                    acceleration->setAcceleration_y(0.0f);
                }
            }
        }
    }
}

/**
 * This function sets the clock for the MoveSystem.
 *
 * @param clock A pointer to the clock that the system will use to determine how
 * much time has passed since the last update.
 */
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