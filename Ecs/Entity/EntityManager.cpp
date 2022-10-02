/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** EntityManager
*/

#include "EntityManager.hpp"
#include <algorithm>

ECS::EntityManager::EntityManager()
{
}

ECS::EntityManager::~EntityManager()
{
}

ECS::Entity ECS::EntityManager::createEntity(ECS::EntityType type) {_entities.push_back(ECS::Entity(_entities.size(), type));} //Need modif to create auto IDs when we set them

void ECS::EntityManager::destroyEntity(ECS::Entity e)
{
    _entities.erase(std::find(_entities.begin(), _entities.end(), e));
    //_eentities.erase(_eentities.find(e));
    /*for (std::size_t i = 0; i < _centities.size(); ++i)
        _centities[i].erase(std::find(_centities[i].begin(), _centities[i].end(), e));*///Problème à résoudre (aucune idée de pourquoi _centities[i] n'est pas possible, la raison la plus présente sur internet c'est concernant des const donc pas compris)
}

std::vector<ECS::Entity> &ECS::EntityManager::getEntities() const
{
    return _entities;
}
