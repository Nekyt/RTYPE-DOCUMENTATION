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

        ECS::Entity createEntity();
        void destroyEntity(ECS::Entity entity);

        template<class System>
        System &addSystem();

        template<class System>
        System &getSystem();

    protected:
    private:
        std::shared_ptr<ECS::EntityManager> _entityManager;
        std::shared_ptr<ECS::ComponentManager> _componentManager;
        std::unique_ptr<ECS::SystemManager> _systemManager;
};

#endif /* !MANAGER_HPP_ */
