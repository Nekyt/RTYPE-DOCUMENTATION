/*
** EPITECH PROJECT, 2022
** B-CPP-500-STG-5-1-rtype-romanie.de-meyer
** File description:
** NetworkServer
*/

#ifndef NETWORKSERVER_HPP_
#define NETWORKSERVER_HPP_

#include <iostream>
#include <SFML/Network.hpp>
#include "../Ecs/Entity/Entity.hpp"
#include "../Ecs/IncludeComponents.hpp"
#include "Enum.hpp"
#include "PacketOperatorSurcharge.hpp"

namespace Network {
class Server {
    public:
        Server() = default;
        ~Server();

        void createConnection();

//      MAIN THREAD -> CREATION OF ROOM + SENDING ROOM LIST

        std::pair<std::pair<sf::IpAddress, unsigned short>, std::pair<Network::Networking, sf::Packet>> retrievePacket();
        int createRoom(int playerNb);
        void sendPacket(std::pair<std::pair<sf::IpAddress, unsigned short>, sf::Packet> packet);
        void sendRoomList(std::pair<sf::IpAddress, unsigned short>, std::vector<int> list);
        void sendPlayerId(std::pair<sf::IpAddress, unsigned short>, int id);
        void sendError(std::pair<sf::IpAddress, unsigned short>, std::string errorMsg);
        void sendEnum(std::pair<sf::IpAddress, unsigned short> client, Network::Networking type);
        void sendGameUpdate(std::pair<sf::IpAddress, unsigned short> client, std::vector<std::pair<ECS::Entity, ECS::Position>>);
        void sendPlayerDeathOrDisconnect(std::pair<sf::IpAddress, unsigned short> client, int id, Network::Networking type);

    private:
        sf::UdpSocket _udp;
        sf::IpAddress _ip;
        unsigned short _port;
};

};

#endif /* !NETWORKSERVER_HPP_ */
