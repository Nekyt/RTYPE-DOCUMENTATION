/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** SystemManager
*/

#ifndef SYSTEMMANAGER_HPP_
#define SYSTEMMANAGER_HPP_

#include "../Component/ComponentManager.hpp"
#include "../Entity/EntityManager.hpp"
#include "../IncludeCpp.hpp"
#include "../IncludeSystem.hpp"

namespace ECS {
class SystemManager {
public:
    SystemManager(const std::shared_ptr<ComponentManager>& componentManager, const std::shared_ptr<EntityManager>& entityManager);
    ~SystemManager() = default;

    template <typename System>
    System& addSystem()
    {
        _systems.emplace(typeid(System), System(_componentManager, _entityManager));
        return std::any_cast<System&>(_systems.at(typeid(System)));
    }

    template <class System>
    System& getSystem()
    {
        return std::any_cast<System&>(_systems[std::type_index(typeid(System).name())]);
    }

protected:
private:
    std::unordered_map<std::type_index, std::any> _systems;
    std::shared_ptr<ComponentManager> _componentManager;
    std::shared_ptr<EntityManager> _entityManager;
};
} // namespace ECS

#endif /* !SYSTEMMANAGER_HPP_ */
