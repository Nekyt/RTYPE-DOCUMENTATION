/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** Manager
*/

#include "Manager.hpp"
#include "System/MoveSystem.hpp"

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
 * It returns a reference to the vector of entities
 *
 * @return A vector of entities.
 */
std::vector<ECS::Entity>& Manager::getEntities()
{
    return _entityManager->getEntities();
}

/**
 * It returns a reference to a vector of entities that have the specified type
 *
 * @return A vector of entities.
 */
std::vector<ECS::Entity> Manager::getEntityByType(ECS::EntityType type)
{
    return _entityManager->getEntityByType(type);
}

/**
 * It returns a reference to a vector of entities that have the given id
 *
 * @return A vector of entities with the given id.
 */
std::vector<ECS::Entity> Manager::getEntityById(std::size_t id)
{
    return _entityManager->getEntityById(id);
}

/**
 * Add a component to an entity.
 *
 * @param e The entity to add the component to
 * @param c The component type to add to the entity.
 */
void Manager::addComponent(ECS::Entity e, ECS::ComponentType c, std::shared_ptr<ECS::IComp> comp)
{
    _componentManager->addComponent(e, c, comp);
}

/**
 * Get a component from the component manager.
 */
std::shared_ptr<ECS::IComp> Manager::getComponent(ECS::Entity e, ECS::ComponentType c)
{
    return _componentManager->getComponent(e, c);
}

/**
 * It returns a map of all the components of a given entity.
 */
std::map<ECS::ComponentType, std::shared_ptr<ECS::IComp>>& Manager::getComponentList(ECS::Entity entity)
{
    return _componentManager->getComponentList(entity);
}

/**
 * Get a list of entities that have a specific component.
 */
std::vector<ECS::Entity>& Manager::getEntityList(ECS::ComponentType type)
{
    return _componentManager->getEntityList(type);
}
