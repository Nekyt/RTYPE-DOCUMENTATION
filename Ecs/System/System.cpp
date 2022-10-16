/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** System
*/

#include "System.hpp"

/**
 * The constructor for the System class.
 *
 * @param componentManager A pointer to the ComponentManager that the System will
 * use to access Components.
 * @param entityManager The entity manager that the system will use to get
 * entities.
 */
ECS::System::System(const std::shared_ptr<ComponentManager>& componentManager, const std::shared_ptr<EntityManager>& entityManager)
{
    _componentManager = componentManager;
    _entityManager = entityManager;
}
