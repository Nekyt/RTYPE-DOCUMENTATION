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
    bool checkIsValidEntity(Entity entity);

protected:
    void setEvents(Entity &entity, Button &event);
    void modifyAcceleration(Entity entity, Button event);
    void shoot(Entity entity);
    void clearEvents();

private:
    std::unordered_map<std::size_t, std::vector<Button>> _currentEvents;
};
} // namespace ECS

#endif /* !EVENTSSYSTEM_HPP_ */
