/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** ShootSystem
*/

#ifndef SHOOTSYSTEM_HPP_
#define SHOOTSYSTEM_HPP_

#include "../Include.hpp"

namespace ECS
{
    class ShootSystem {
        public:
            ShootSystem();
            ~ShootSystem();

            void update();
            bool checkIsValidEntity(const std::size_t id);

        protected:
        private:
    };
} // namespace ECS

#endif /* !SHOOTSYSTEM_HPP_ */
