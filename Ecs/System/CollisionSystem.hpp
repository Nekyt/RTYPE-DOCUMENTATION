/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** CollisionSystem
*/

#ifndef COLLISIONSYSTEM_HPP_
#define COLLISIONSYSTEM_HPP_

#include "./System.hpp"

namespace ECS {
class CollisionSystem : public System {
public:
    CollisionSystem(const std::shared_ptr<ComponentManager>& componentsManager, const std::shared_ptr<EntityManager>& entityManager);
    ~CollisionSystem() = default;

    void update();
    bool checkIsValidEntity(Entity entity);

protected:
    void bonusCollisionManagement(Entity entityPlayer, Entity entityBonus);
private:
};
} // namespace ECS

#endif /* !COLLISIONSYSTEM_HPP_ */
