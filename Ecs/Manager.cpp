/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** Manager
*/

#include "Manager.hpp"

Manager::Manager()
{
    _entityManager = std::make_shared<ECS::EntityManager>();
    _componentManager = std::make_shared<ECS::ComponentManager>();
    _systemManager = std::make_unique<ECS::SystemManager>(_componentManager, _entityManager);
}

ECS::Entity Manager::createEntity()
{
    return _entityManager->createEntity();
}

void Manager::destroyEntity(ECS::Entity entity)
{
    //_entityManager->destroyEntity(entity);
}

template<class System>
System &Manager::addSystem()
{
    return _systemManager->addSystem<System>();
}

template<class System>
System &Manager::getSystem()
{
    return _systemManager->getSystem<System>();
}
