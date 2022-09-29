/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** SystemManager
*/

#include "SystemManager.hpp"

ECS::SystemManager::SystemManager(const std::shared_ptr<ComponentManager> &componentManager, const std::shared_ptr<EntityManager> &entityManager) : _componentManager(componentManager), _entityManager(entityManager)
{
}

template<class System>
System &ECS::SystemManager::addSystem()
{
    _systems.emplace(typeid(System).name() std::any_cast<System>(_componentManager, _entityManager));
    return std::any_cast<System &>(_systems[typeid(System).name()]);
}

template<class System>
System &ECS::SystemManager::getSystem()
{
    return std::any_cast<System &>(_systems.at(System));
}
