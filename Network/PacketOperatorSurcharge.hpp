#include <SFML/Network.hpp>
#include <deque>
#include <utility>
#include "../Ecs/Component/include/Position.hpp"
#include "../Ecs/Entity/Entity.hpp"
#include "../Graphics/Events.hpp"
#include <list>
#include <deque>

inline sf::Packet& operator <<(sf::Packet& packet, const std::deque<int>& p)
{
    packet << static_cast<int>(p.size());
    for (size_t i = 0; i < p.size(); ++i) {
        packet << p[i];
    }
    return packet;
}

inline std::deque<int>& operator >>(sf::Packet& packet, std::deque<int>& p)
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

inline sf::Packet& operator <<(sf::Packet& packet, const std::deque<std::pair<ECS::Entity, ECS::Position>>& p)
{
    packet << static_cast<int>(p.size());
    for (size_t i = 0; i < p.size(); ++i) {
        packet << static_cast<int>(p[i].first.getId()) << static_cast<int>(p[i].first.getType());
        packet << static_cast<int>(p[i].second.getPosition_x()) << static_cast<int>(p[i].second.getPosition_y());
    }
    return packet;
}

inline std::deque<std::pair<ECS::Entity, ECS::Position>>& operator >>(sf::Packet& packet, std::deque<std::pair<ECS::Entity, ECS::Position>>& p)
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

inline sf::Packet& operator <<(sf::Packet& packet, const std::deque<Button>& p)
{
    packet << static_cast<int>(p.size());
    for (size_t i = 0; i < p.size(); ++i)
        packet << static_cast<int>(p[i]);
    return packet;
}

inline std::deque<Button>& operator >>(sf::Packet& packet, std::deque<Button>& p)
{
    int size;
    int elem;

    packet >> size;
    for (int i = 0; i < size; ++i) {
        packet >> elem;
        p.push_back(static_cast<Button>(elem));
    }
    return p;
}