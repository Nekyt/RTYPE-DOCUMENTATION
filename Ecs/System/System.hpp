/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** System
*/

#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include "../IncludeCpp.hpp"
#include "../Entity/EntityManager.hpp"
#include "../Component/ComponentManager.hpp"

namespace ECS
{
    class System {
        public:
            System(const std::shared_ptr<ComponentManager> &componentManager, const std::shared_ptr<EntityManager> &entityManager);
            ~System() = default;

            void Update();

        protected:
            std::shared_ptr<ComponentManager> _componentManager;
            std::shared_ptr<EntityManager> _entityManager;
        private:
    };
} // namespace ECS

#endif /* !SYSTEM_HPP_ */