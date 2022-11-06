/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** EventsSystem
*/

#ifndef EVENTSSYSTEM_HPP_
#define EVENTSSYSTEM_HPP_

#include "./System.hpp"

namespace ECS {
class EventsSystem : public System {
public:
    EventsSystem(const std::shared_ptr<ComponentManager>& componentsManager, const std::shared_ptr<EntityManager>& entityManager);
    ~EventsSystem() = default;

    void update();
    void setSfml(std::shared_ptr<InitSfml> sfml);
    void setClock(std::shared_ptr<Clock> clock);
    bool checkIsValidEntity(Entity entity);
    void setEvents(std::size_t entity, Button& event);
    void clearEvents();

protected:
    void modifyAcceleration(Entity entity, Button event);
    void shoot(Entity entity);

private:
    std::unordered_map<std::size_t, std::vector<Button>> _currentEvents;
    std::shared_ptr<InitSfml> _sfml;
    std::shared_ptr<Clock> _clock;
};
} // namespace ECS

#endif /* !EVENTSSYSTEM_HPP_ */
