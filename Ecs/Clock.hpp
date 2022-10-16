#include "./Component/ComponentManager.hpp"
#include <chrono>
#include <map>
#include <utility>
#include <vector>

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
    std::map<size_t, std::map<ECS::ComponentType, std::clock_t>> _previousIte;
    std::map<size_t, std::map<ECS::ComponentType, int>> _timer;
};