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
ECS::SystemManager::SystemManager(const std::shared_ptr<ComponentManager>& componentManager, const std::shared_ptr<EntityManager>& entityManager)
    : _componentManager(componentManager)
    , _entityManager(entityManager)
{
}
