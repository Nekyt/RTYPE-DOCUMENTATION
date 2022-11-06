/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** EntityManager
*/

#include "EntityManager.hpp"
#include <algorithm>

/**
 * It creates an entity and adds it to the entity manager
 *
 * @param type The type of entity you want to create.
 *
 * @return A reference to the last element in the vector.
 */
ECS::Entity ECS::EntityManager::createEntity(ECS::EntityType type)
{
    _entities.push_back(ECS::Entity(_entities.size(), type));
    return _entities.at(_entities.size() - 1);
} // Need modif to create auto IDs when we set them

/**
 * It removes the entity from the list of entities
 *
 * @param e The entity to destroy.
 */
void ECS::EntityManager::destroyEntity(ECS::Entity e)
{
    _entities.erase(std::find(_entities.begin(), _entities.end(), e));
    //_eentities.erase(_eentities.find(e));
    /*for (std::size_t i = 0; i < _centities.size(); ++i)
        _centities[i].erase(std::find(_centities[i].begin(), _centities[i].end(), e));*/
    // Problème à résoudre (aucune idée de pourquoi _centities[i] n'est pas possible, la raison la plus présente sur internet c'est concernant des const donc pas compris)
}

/**
 * Returns a reference to the vector of entities.
 *
 * @return A reference to the vector of entities.
 */
std::vector<ECS::Entity>& ECS::EntityManager::getEntities()
{
    return _entities;
}

std::vector<ECS::Entity> ECS::EntityManager::getEntityByType(EntityType type)
{
    std::vector<Entity> entitiesByType;

    for (auto& entity : _entities)
        if (entity.getType() == type)
            entitiesByType.push_back(entity);
    return entitiesByType;
}

std::vector<ECS::Entity> ECS::EntityManager::getEntityById(std::size_t id)
{
    std::vector<Entity> entitiesById;

    for (auto& entity : _entities)
        if (entity.getId() == id)
            entitiesById.push_back(entity);
    return entitiesById;
}