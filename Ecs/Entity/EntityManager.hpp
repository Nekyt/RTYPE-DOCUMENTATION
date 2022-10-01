/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** EntityManager
*/

#ifndef ENTITYMANAGER_HPP_
#define ENTITYMANAGER_HPP_

#include "Entity.hpp"
//#include "../../../include/include.hpp" //Include de tout les components
#include <set>
#include <map>
#include <vector>

namespace ECS
{
    enum EntityType {PLAYER, ENEMY, PROJECTILES, OBSTACLES, GRAPHICS};
    enum ComponentType {ACCELERATION, BONUS, PATTERN, SPEED, POSITION, DAMAGE, ROTATION, SOUND, HEALTH, HITBOX, SIZE, CONTROLABLE, IDE, TEXT, TEXTURE, WEAPON};
    class EntityManager {
        public:
            EntityManager();
            ~EntityManager();

            Entity createEntity(EntityType t);
            void destroyEntity(Entity e);

            Entity &getEntities() const;

            void addComponent(Entity e, ComponentType c);
            IComp getComponent(Entity e, ComponentType c);

        private:
            IComp createComponent(ComponentType c);
            std::vector<Entity> _entities;
            std::map<Entity, std::map<ComponentType, IComp>> _eentities;
            std::map<ComponentType, std::vector<Entity>> _centities;
    };
} // namespace ECS

#endif /* !ENTITYMANAGER_HPP_ */
