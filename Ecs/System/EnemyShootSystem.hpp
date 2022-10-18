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
    void setClock(std::shared_ptr<Clock> clock);
    bool checkIsValidEntity(Entity entity);

protected:
private:
    std::shared_ptr<InitSfml> _sfml;
    std::shared_ptr<Clock> _clock;
};
} // namespace ECS

#endif /* !ENEMYSHOOTSYSTEM_HPP_ */
