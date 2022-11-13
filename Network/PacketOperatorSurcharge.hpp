#pragma once
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
    std::cout << "Buttons size : " << static_cast<int>(p.size()) << " : " << std::endl;
    packet << static_cast<int>(p.size());
    for (size_t i = 0; i < p.size(); ++i) {
        packet << static_cast<int>(p[i]);
        std::cout << static_cast<int>(p[i]) << " ";
    }
    std::cout << std::endl << std::endl;
    return packet;
}

inline std::deque<Button>& operator >>(sf::Packet& packet, std::deque<Button>& p)
{
    int size;
    int elem;

    packet >> size;
    std::cout << "Buttons size : " << size << std::endl;
    for (int i = 0; i < size; ++i) {
        packet >> elem;
        p.push_back(static_cast<Button>(elem));
    }
    return p;
}
//std::deque<std::pair<size_t, std::pair<int, int>>>

inline sf::Packet& operator <<(sf::Packet& packet, const std::deque<std::pair<size_t, std::pair<int, int>>>& p)
{
    packet << static_cast<int>(p.size());
    for (size_t i = 0; i < p.size(); ++i)
        packet << static_cast<int>(p[i].first) << p[i].second.first << p[i].second.second;
    return packet;
}

inline std::deque<std::pair<size_t, std::pair<int, int>>>& operator >>(sf::Packet& packet, std::deque<std::pair<size_t, std::pair<int, int>>>& p)
{
    int size;
    int roomId;
    int playersMax;
    int playerNb;

    packet >> size;
    for (int i = 0; i < size; ++i) {
        packet >> roomId >> playersMax >> playerNb;
        p.push_back(std::make_pair(static_cast<size_t>(roomId), std::make_pair(playersMax, playerNb)));
    }
    return p;
}

inline sf::Packet& operator <<(sf::Packet& packet, const std::pair<sf::IpAddress, unsigned short>& p)
{
    packet << p.first.toString() << static_cast<int>(p.second);
    return packet;
}

inline std::pair<sf::IpAddress, unsigned short>& operator >>(sf::Packet& packet, std::pair<sf::IpAddress, unsigned short>& p)
{
    std::string ip;
    int port;

    packet >> ip >> port;
    p = std::make_pair(static_cast<sf::IpAddress>(ip), static_cast<unsigned short>(port));
    return p;
}