/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** ComponentManager
*/

#include "ComponentManager.hpp"

/**
 * It adds a component to an entity
 *
 * @param e The entity to add the component to.
 * @param c The component type
 */
void ECS::ComponentManager::addComponent(ECS::Entity e, ECS::ComponentType c, std::shared_ptr<IComp> comp)
{
    std::map<ComponentType, std::shared_ptr<IComp>> compo;

    if (_eentities.find(e) == _eentities.end()) {
        compo.insert(std::pair<ComponentType, std::shared_ptr<IComp>>(c, comp));
        _eentities.insert(std::pair<Entity, std::map<ComponentType, std::shared_ptr<IComp>>>(e, compo));
        _centities[c].push_back(e);
    } else {
        _eentities[e].insert(std::pair<ComponentType, std::shared_ptr<IComp>>(c, comp));
        _centities[c].push_back(e);
    }
}

/**
 * It returns a reference to the component of type c of entity e
 *
 * @return A reference to the component of type c of entity e.
 */
std::shared_ptr<ECS::IComp> ECS::ComponentManager::getComponent(ECS::Entity e, ECS::ComponentType c)
{
    return _eentities[e][c];
}

/**
 * It returns a reference to the map of components for the given entity
 *
 * @return A map of component types and components.
 */
std::map<ECS::ComponentType, std::shared_ptr<ECS::IComp>>& ECS::ComponentManager::getComponentList(Entity entity)
{
    return _eentities.at(entity);
}

/**
 * It returns a reference to the deque of entities that have the specified
 * component type
 *
 * @return A deque of entities.
 */
std::deque<ECS::Entity>& ECS::ComponentManager::getEntityList(ComponentType type)
{
    return _centities.at(type);
}