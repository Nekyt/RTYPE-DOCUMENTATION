/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** SystemManager
*/

#include "SystemManager.hpp"

/**
 * It's a constructor for the SystemManager class
 * 
 * @param componentManager The ComponentManager that the SystemManager will use to
 * get components from.
 * @param entityManager The entity manager that the system manager will use to get
 * entities.
 */
ECS::SystemManager::SystemManager(const std::shared_ptr<ComponentManager> &componentManager, const std::shared_ptr<EntityManager> &entityManager) : _componentManager(componentManager), _entityManager(entityManager)
{
}

template<class System>
/**
 * It adds a system to the system manager
 * 
 * @return A reference to the system that was just added.
 */
System &ECS::SystemManager::addSystem()
{
    _systems.emplace(typeid(System).name() std::any_cast<System>(_componentManager, _entityManager));
    return std::any_cast<System &>(_systems[typeid(System).name()]);
}

template<class System>
/**
 * It returns a reference to the system of the specified type
 * 
 * @return A reference to the system.
 */
System &ECS::SystemManager::getSystem()
{
    return std::any_cast<System &>(_systems.at(System));
}
