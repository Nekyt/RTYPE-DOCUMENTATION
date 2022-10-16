/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** EnemyShootSystem
*/

#ifndef ENEMYSHOOTSYSTEM_HPP_
#define ENEMYSHOOTSYSTEM_HPP_

#include "./System.hpp"

namespace ECS {
class EnemyShootSystem : public System {
    public:
        EnemyShootSystem(const std::shared_ptr<ComponentManager>& componentsManager, const std::shared_ptr<EntityManager>& entityManager);
        ~EnemyShootSystem() = default;

        void update();
        void setSfml(std::shared_ptr<InitSfml> sfml);
        bool checkIsValidEntity(Entity entity);

    protected:
    private:
        std::shared_ptr<InitSfml> _sfml;
};
} // namespace ECS

#endif /* !ENEMYSHOOTSYSTEM_HPP_ */
