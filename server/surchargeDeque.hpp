#include <deque>
#include <memory>
#include "../Ecs/Entity/Entity.hpp"

inline std::deque<ECS::Entity> operator +(std::deque<ECS::Entity> a, std::deque<ECS::Entity> b)
{
    for (size_t i = 0; i < b.size(); ++i)
        a.push_back(b[i]);
    return a;
}