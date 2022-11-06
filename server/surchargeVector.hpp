#include <vector>
#include <memory>
#include "../Ecs/Entity/Entity.hpp"

inline std::vector<ECS::Entity> operator +(std::vector<ECS::Entity> a, std::vector<ECS::Entity> b)
{
    for (size_t i = 0; i < b.size(); ++i)
        a.push_back(b[i]);
    return a;
}