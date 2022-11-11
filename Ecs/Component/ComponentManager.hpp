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

namespace ECS {
enum ComponentType { ACCELERATION,
    BONUS,
    PATTERN,
    SPEED,
    BULLET,
    POSITION,
    DAMAGE,
    ROTATION,
    SOUND,
    HEALTH,
    HITBOX,
    SIZE,
    CONTROLABLE,
    IDE,
    TEXT,
    SPRITE,
    WEAPON,
    NETWORK };
class ComponentManager {
public:
    ComponentManager() = default;
    ~ComponentManager() = default;

    void addComponent(Entity e, ComponentType c, std::shared_ptr<IComp> comp);
    std::shared_ptr<IComp> getComponent(Entity e, ComponentType c);

    std::map<ComponentType, std::shared_ptr<IComp>>& getComponentList(Entity entity);
    std::deque<Entity>& getEntityList(ComponentType type);

protected:
private:
    std::map<Entity, std::map<ComponentType, std::shared_ptr<IComp>>> _eentities;
    std::map<ComponentType, std::deque<Entity>> _centities;
};
} // namespace ECS

#endif /* !COMPONENTMANAGER_HPP_ */
