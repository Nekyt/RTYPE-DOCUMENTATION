/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** BonusSystem
*/

#ifndef BONUSSYSTEM_HPP_
#define BONUSSYSTEM_HPP_

#include "./System.hpp"

namespace ECS
{
    class BonusSystem : public System {
    public:
        BonusSystem(const std::shared_ptr<ComponentManager>& componentsManager, const std::shared_ptr<EntityManager>& entityManager);
        ~BonusSystem() = default;

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

#endif /* !BONUSSYSTEM_HPP_ */
