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

/**
 * It creates an entity and returns it
 * 
 * @param type The type of entity you want to create.
 * 
 * @return An entity.
 */
ECS::Entity Manager::createEntity(ECS::EntityType type)
{
    return _entityManager->createEntity(type);
}

/**
 * This function destroys an entity.
 * 
 * @param entity The entity to destroy.
 */
void Manager::destroyEntity(ECS::Entity entity)
{
    _entityManager->destroyEntity(entity);
}

/**
 * Add a component to an entity.
 * 
 * @param e The entity to add the component to
 * @param c The component type to add to the entity.
 */
void Manager::addComponent(ECS::Entity e, ECS::ComponentType c)
{
    _componentManager->addComponent(e, c);
}

/**
 * Get a component from the component manager.
 */
ECS::IComp &Manager::getComponent(ECS::Entity e, ECS::ComponentType c)
{
    _componentManager->getComponent(e, c);
}

/**
 * It returns a map of all the components of a given entity.
 */
std::map<ECS::ComponentType, ECS::IComp> &Manager::getComponentList(ECS::Entity entity)
{
    _componentManager->getComponentList(entity);
}

/**
 * Get a list of entities that have a specific component.
 */
std::vector<ECS::Entity> &Manager::getEntityList(ECS::ComponentType type)
{
    _componentManager->getEntityList(type);
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
