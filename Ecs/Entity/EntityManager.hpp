/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** EntityManager
*/

#ifndef ENTITYMANAGER_HPP_
#define ENTITYMANAGER_HPP_

#include "Entity.hpp"
#include <set>
#include <map>

namespace ECS
{
    class EntityManager {
        public:
            EntityManager();
            ~EntityManager();

            Entity createEntity();
            void destroyEntity();

            std::set<Entity> getEntities() const;

            //void addComponent(Entity e, Type t, Component c);
            //Component getComponent(Entity e, Type t);

        protected:
        private:
            //std::map<Entity, std::set<ComponentType>> m_entities;
            //std::map<Entity, std::set<Component>> m_entities;
    };
} // namespace ECS

#endif /* !ENTITYMANAGER_HPP_ */
