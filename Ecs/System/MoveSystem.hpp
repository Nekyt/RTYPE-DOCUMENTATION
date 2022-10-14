/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** MoveSystem
*/

#ifndef MOVESYSTEM_HPP_
#define MOVESYSTEM_HPP_

#include "./System.hpp"
namespace ECS
{
    class MoveSystem : public System {
        public:
            MoveSystem(const std::shared_ptr<ComponentManager> &componentsManager, const std::shared_ptr<EntityManager> &entityManager);
            ~MoveSystem() = default;

            void update();
            bool checkIsValidEntity(Entity entity);

        protected:
        private:
    };
} // namespace ECS

#endif /* !MOVESYSTEM_HPP_ */
