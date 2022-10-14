/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** ShootSystem
*/

#include "ShootSystem.hpp"

ECS::ShootSystem::ShootSystem(const std::shared_ptr<ComponentManager> &componentsManager, const std::shared_ptr<EntityManager> &entityManager) : System(componentsManager, entityManager)
{
}
