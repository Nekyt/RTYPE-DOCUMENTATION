/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** MoveSystem
*/

#ifndef MOVESYSTEM_HPP_
#define MOVESYSTEM_HPP_

#include "./System.hpp"
namespace ECS {
class MoveSystem : public System {
public:
    MoveSystem(const std::shared_ptr<ComponentManager>& componentsManager, const std::shared_ptr<EntityManager>& entityManager);
    ~MoveSystem() = default;

    void update();
    void setClock(std::shared_ptr<Clock> clock);
    bool checkIsValidEntity(Entity entity);

protected:
private:
    std::shared_ptr<Clock> _clock;
};
} // namespace ECS

#endif /* !MOVESYSTEM_HPP_ */
