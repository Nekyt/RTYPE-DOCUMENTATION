/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** PatternSystem
*/

#ifndef PATTERNSYSTEM_HPP_
#define PATTERNSYSTEM_HPP_

#include "./System.hpp"

namespace ECS
{
class PatternSystem : public System {
    public:
        PatternSystem(const std::shared_ptr<ComponentManager>& componentsManager, const std::shared_ptr<EntityManager>& entityManager);
        ~PatternSystem() = default;

        void update();
        void setClock(std::shared_ptr<Clock> clock);
        bool checkIsValidEntity(Entity entity);

    protected:
    private:
        std::shared_ptr<Clock> _clock;
};
} // namespace ECS




#endif /* !PATTERNSYSTEM_HPP_ */
