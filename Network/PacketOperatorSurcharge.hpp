#include <SFML/Network.hpp>
#include <vector>
#include <utility>
#include "../Ecs/Component/include/Position.hpp"
#include "../Ecs/Entity/Entity.hpp"

inline sf::Packet& operator <<(sf::Packet& packet, const std::vector<int>& p)
{
    packet << static_cast<int>(p.size());
    for (size_t i = 0; i < p.size(); ++i) {
        packet << p[i];
    }
    return packet;
}

inline std::vector<int>& operator >>(sf::Packet& packet, std::vector<int>& p)
{
    int size = 0;
    int elem = 0;

    packet >> size;
    for (int i = 0; i < size; ++i) {
        packet >> elem;
        p.push_back(elem);
    }
    return p;
}

inline sf::Packet& operator <<(sf::Packet& packet, const std::vector<std::pair<ECS::Entity, ECS::Position>>& p)
{
    packet << static_cast<int>(p.size());
    for (size_t i = 0; i < p.size(); ++i) {
        packet << static_cast<int>(p[i].first.getId()) << static_cast<int>(p[i].first.getType());
        packet << static_cast<int>(p[i].second.getPosition_x()) << static_cast<int>(p[i].second.getPosition_y());
    }
    return packet;
}

inline std::vector<std::pair<ECS::Entity, ECS::Position>>& operator >>(sf::Packet& packet, std::vector<std::pair<ECS::Entity, ECS::Position>>& p)
{
    int size = 0;
    int id, type, posx, posy = 0;

    packet >> size;
    for (int i = 0; i < size; ++i) {
        packet >> id >> type >> posx >> posy;
        p.push_back(std::make_pair(ECS::Entity(static_cast<size_t>(id), static_cast<ECS::EntityType>(type)), ECS::Position(posx, posy)));
    }
    return p;
}