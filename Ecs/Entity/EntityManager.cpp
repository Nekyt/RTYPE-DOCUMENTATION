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
    _eentities.erase(_eentities.find(e));
    /*for (std::size_t i = 0; i < _centities.size(); ++i)
        _centities[i].erase(std::find(_centities[i].begin(), _centities[i].end(), e));*///Problème à résoudre (aucune idée de pourquoi _centities[i] n'est pas possible, la raison la plus présente sur internet c'est concernant des const donc pas compris)
}

void ECS::EntityManager::addComponent(ECS::Entity e, ECS::ComponentType c)
{
    std::map<ComponentType, IComp> compo;

    if (_eentities.find(e) == _eentities.end()) {
        compo.insert(std::pair<ComponentType, IComp>(c, createComponent(c)));
        _eentities.insert(std::pair<Entity, std::map<ComponentType, IComp>>(e, compo));
        _centities[c].push_back(e);
    } else {
        _eentities[e].insert(std::pair<ComponentType, IComp>(c, createComponent(c)));
        _centities[c].push_back(e);
    }
}

ECS::IComp ECS::EntityManager::getComponent(ECS::Entity e, ECS::ComponentType c)
{
    return _eentities[e][c];
}

ECS::IComp ECS::EntityManager::createComponent(ECS::ComponentType c)
{
    if (c == ECS::ComponentType::ACCELERATION)
        return ECS::Acceleration();
    else if (c == ECS::ComponentType::BONUS)
        return ECS::Bonus();
    else if (c == ECS::ComponentType::CONTROLABLE)
        return ECS::Controlable(true);
    else if (c == ECS::ComponentType::PATTERN)
        return ECS::Pattern();
    else if (c == ECS::ComponentType::SPEED)
        return ECS::Speed(0);
    else if (c == ECS::ComponentType::POSITION)
        return ECS::Position(0, 0);
    else if (c == ECS::ComponentType::DAMAGE)
        return ECS::Damage(0);
    else if (c == ECS::ComponentType::ROTATION)
        return ECS::Rotation(0);
    else if (c == ECS::ComponentType::SOUND)
        return ECS::Sound();
    else if (c == ECS::ComponentType::HEALTH)
        return ECS::Health(0);
    else if (c == ECS::ComponentType::HITBOX)
        return ECS::Hitbox(0, 0);
    else if (c == ECS::ComponentType::SIZE)
        return ECS::Size(0, 0);
    else if (c == ECS::ComponentType::IDE)
        return ECS::ID(0);
    else if (c == ECS::ComponentType::TEXT)
        return ECS::Text(std::string(""));
    else if (c == ECS::ComponentType::TEXTURE)
        return ECS::Texture();
    else if (c == ECS::ComponentType::WEAPON)
        return ECS::Weapon();
}