/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** Manager
*/

#include "Manager.hpp"

/**
 * The constructor for the Manager class creates a new EntityManager,
 * ComponentManager, and SystemManager
 */
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
/**
 * It adds a system to the system manager
 * 
 * @return A reference to the system that was added.
 */
System &Manager::addSystem()
{
    return _systemManager->addSystem<System>();
}

template<class System>
/**
 * It returns a reference to the system of type `System` that is managed by the
 * `SystemManager`
 * 
 * @return A reference to the System object.
 */
System &Manager::getSystem()
{
    return _systemManager->getSystem<System>();
}
