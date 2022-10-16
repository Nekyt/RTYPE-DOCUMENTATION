#include "../../Ecs/Component/ComponentManager.hpp"
#include <map>
#include <vector>
#include <utility>
#include <chrono>

class Clock {
    public:
        Clock() = default;
        ~Clock() = default;
        void addClockComponent(size_t entityId, ECS::ComponentType type, int updateTime);
        std::vector<std::pair<size_t, std::vector<ECS::ComponentType>>> getEntitiesToUpdate();
        int componentUpdateNumber(size_t entity, ECS::ComponentType type);
        void eraseClockComponent(size_t entityId, ECS::ComponentType, bool debug = false);
        void eraseClock(size_t entityId);

    private:
        std::vector<size_t> _entities;
        std::map<size_t, std::vector<ECS::ComponentType>> _timersList;
        std::map<size_t, std::map<ECS::ComponentType, std::time_t>> _previousIte;
        std::map<size_t, std::map<ECS::ComponentType, int>> _timer;
};