#ifndef CLOCK_HPP
#define CLOCK_HPP

#include "./Component/ComponentManager.hpp"
#include <chrono>
#include <map>
#include <utility>
#include <deque>

class Clock {
public:
    Clock() = default;
    ~Clock() = default;
    void addClockComponent(size_t entityId, ECS::ComponentType type, int updateTime);
    std::deque<std::pair<size_t, std::deque<ECS::ComponentType>>> getEntitiesToUpdate();
    int componentUpdateNumber(size_t entity, ECS::ComponentType type);
    void eraseClockComponent(size_t entityId, ECS::ComponentType, bool debug = false);
    void eraseClock(size_t entityId);

private:
    std::deque<size_t> _entities;
    std::map<size_t, std::deque<ECS::ComponentType>> _timersList;
    std::map<size_t, std::map<ECS::ComponentType, std::clock_t>> _previousIte;
    std::map<size_t, std::map<ECS::ComponentType, int>> _timer;
};

#endif