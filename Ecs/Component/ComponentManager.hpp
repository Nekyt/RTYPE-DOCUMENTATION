/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** ComponentManager
*/

#ifndef COMPONENTMANAGER_HPP_
#define COMPONENTMANAGER_HPP_

#include "../Entity/EntityManager.hpp"
#include "../IncludeComponents.hpp"


namespace ECS
{
    enum ComponentType {ACCELERATION, BONUS, PATTERN, SPEED, POSITION, DAMAGE, ROTATION, SOUND, HEALTH, HITBOX, SIZE, CONTROLABLE, IDE, TEXT, TEXTURE, WEAPON};
    class ComponentManager {
        public:
            ComponentManager() = default;
            ~ComponentManager() = default;

            void addComponent(Entity e, ComponentType c);
            IComp &getComponent(Entity e, ComponentType c);

            std::map<ComponentType, IComp> &getComponentList(Entity entity);
            std::vector<Entity> &getEntityList(ComponentType type);

        protected:
        private:
            IComp createComponent(ComponentType c);
            std::map<Entity, std::map<ComponentType, IComp>> _eentities;
            std::map<ComponentType, std::vector<Entity>> _centities;
    };
} // namespace ECS

#endif /* !COMPONENTMANAGER_HPP_ */
