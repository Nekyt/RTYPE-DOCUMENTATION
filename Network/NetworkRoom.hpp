/*
** EPITECH PROJECT, 2022
** B-CPP-500-STG-5-1-rtype-romanie.de-meyer
** File description:
** NetworkRoom
*/

#ifndef NETWORKROOM_HPP_
#define NETWORKROOM_HPP_

#include <iostream>
#include <SFML/Network.hpp>
#include "../Ecs/Entity/Entity.hpp"
#include "../Ecs/IncludeComponents.hpp"
#include "Enum.hpp"
#include "PacketOperatorSurcharge.hpp"

namespace Network {
class Room {
    public:
        Room() = default;
        ~Room();

        void createConnection(int roomId);

        std::pair<std::pair<sf::IpAddress, unsigned short>, std::pair<Network::Networking, sf::Packet>> retrievePacket();
        void sendPacket(std::pair<std::pair<sf::IpAddress, unsigned short>, sf::Packet> packet);
        void sendError(std::pair<sf::IpAddress, unsigned short>, std::string errorMsg);

    private:
        sf::UdpSocket _udp;
        sf::IpAddress _ip;
        unsigned short _port;
        int _roomId;
};

};

#endif /* !NETWORKROOM_HPP_ */
