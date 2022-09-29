/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** MoveSystem
*/

#ifndef MOVESYSTEM_HPP_
#define MOVESYSTEM_HPP_

#include "../Include.hpp"

namespace ECS
{
    class MoveSystem {
        public:
            MoveSystem();
            ~MoveSystem() = default;

            void update();
            bool checkIsValidEntity(const std::size_t id);

        protected:
        private:
    };
} // namespace ECS

#endif /* !MOVESYSTEM_HPP_ */
