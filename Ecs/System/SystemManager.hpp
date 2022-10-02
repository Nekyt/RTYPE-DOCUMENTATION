/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** SystemManager
*/

#ifndef SYSTEMMANAGER_HPP_
#define SYSTEMMANAGER_HPP_

#include "./Entity/EntityManager.hpp"
#include "./Component/ComponentManager.hpp"
#include "../IncludeCpp.hpp"

namespace ECS
{
    enum SystemTypes {MoveSystem, GraphicsSystem};
    class SystemManager {
        public:
            SystemManager(const std::shared_ptr<ComponentManager> &componentManager, const std::shared_ptr<EntityManager> &entityManager);
            ~SystemManager() = default;

            template<class System>
            System &addSystem();

            template<class System>
            System &getSystem();

        protected:
        private:
            std::unordered_map<SystemTypes, std::any> _systems;
            std::shared_ptr<ComponentManager> _componentManager;
            std::shared_ptr<EntityManager> _entityManager;
    };
} // namespace ECS

#endif /* !SYSTEMMANAGER_HPP_ */
