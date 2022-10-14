/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** ShootSystem
*/

#ifndef SHOOTSYSTEM_HPP_
#define SHOOTSYSTEM_HPP_

#include "./System.hpp"

namespace ECS
{
    class ShootSystem : public System {
        public:
            ShootSystem(const std::shared_ptr<ComponentManager> &componentsManager, const std::shared_ptr<EntityManager> &entityManager);
            ~ShootSystem() = default;

            void update();
            bool checkIsValidEntity(const std::size_t id);

        protected:
        private:
    };
} // namespace ECS

#endif /* !SHOOTSYSTEM_HPP_ */
