/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** PatternSystem
*/

#include "PatternSystem.hpp"

ECS::PatternSystem::PatternSystem(const std::shared_ptr<ComponentManager>& componentsManager, const std::shared_ptr<EntityManager>& entityManager)
    : System(componentsManager, entityManager)
{
}

void ECS::PatternSystem::update()
{
    const auto& entities = _entityManager->getEntities();
    std::deque<std::pair<size_t, std::deque<ECS::ComponentType>>> enti = _clock->getEntitiesToUpdate();

    for (const auto& entity : entities) {
        if (entity.getType() != ECS::EntityType::ENEMY)
            continue;
        for (size_t i = 0; i < enti.size(); ++i) {
            if (entity.getId() != enti[i].first || !checkIsValidEntity(entity))
                continue;
            for (size_t j = 0; j < enti.at(i).second.size(); ++j)
                if (enti.at(i).second.at(j) != ECS::ComponentType::PATTERN)
                    continue;
        }
        if (_clock->componentUpdateNumber(entity.getId(), ECS::PATTERN)) {
            std::shared_ptr<ECS::Position> position = std::dynamic_pointer_cast<ECS::Position>(_componentManager->getComponent(entity, ComponentType::POSITION));
            std::shared_ptr<ECS::Speed> speed = std::dynamic_pointer_cast<ECS::Speed>(_componentManager->getComponent(entity, ComponentType::SPEED));
            std::shared_ptr<ECS::Pattern> pattern = std::dynamic_pointer_cast<ECS::Pattern>(_componentManager->getComponent(entity, ComponentType::PATTERN));
            std::shared_ptr<ECS::Acceleration> acceleration = std::dynamic_pointer_cast<ECS::Acceleration>(_componentManager->getComponent(entity, ComponentType::ACCELERATION));
            pattern->getNextPosition(acceleration, speed, position);
        }
    }
}

void ECS::PatternSystem::setClock(std::shared_ptr<Clock> clock)
{
    _clock = clock;
}

bool ECS::PatternSystem::checkIsValidEntity(Entity entity)
{
    auto& components = _componentManager->getComponentList(entity);

    try {
        components.at(ComponentType::PATTERN);
        components.at(ComponentType::SPEED);
        components.at(ComponentType::POSITION);
        return true;
    } catch (const std::exception& e) {
        return false;
    }
}