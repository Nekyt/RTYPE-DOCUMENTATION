/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** Manager
*/

#ifndef MANAGER_HPP_
#define MANAGER_HPP_

#include "System/SystemManager.hpp"

class Manager {
public:
    Manager();
    ~Manager() = default;

    ECS::Entity createEntity(ECS::EntityType type);
    void destroyEntity(ECS::Entity entity);
    std::deque<ECS::Entity>& getEntities();
    std::deque<ECS::Entity> getEntityByType(ECS::EntityType type);
    ECS::Entity getEntityById(std::size_t id);

    void addComponent(ECS::Entity e, ECS::ComponentType c, std::shared_ptr<ECS::IComp> comp);
    std::shared_ptr<ECS::IComp> getComponent(ECS::Entity e, ECS::ComponentType c);
    std::map<ECS::ComponentType, std::shared_ptr<ECS::IComp>>& getComponentList(ECS::Entity entity);
    std::deque<ECS::Entity>& getEntityList(ECS::ComponentType type);

    template <typename System>
    System& addSystem()
    {
        return _systemManager->addSystem<System>();
    }
    template <class System>
    System& getSystem()
    {
        return _systemManager->getSystem<System>();
    }

protected:
private:
    std::shared_ptr<ECS::EntityManager> _entityManager;
    std::shared_ptr<ECS::ComponentManager> _componentManager;
    std::unique_ptr<ECS::SystemManager> _systemManager;
};

#endif /* !MANAGER_HPP_ */
