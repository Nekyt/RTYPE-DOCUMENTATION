/*
** EPITECH PROJECT, 2022
** B-CPP-500-STG-5-1-rtype-romanie.de-meyer
** File description:
** NetworkServer
*/

#ifndef NETWORKSERVER_HPP_
#define NETWORKSERVER_HPP_

#include "../Ecs/Entity/Entity.hpp"
#include "../Ecs/IncludeComponents.hpp"
#include "Enum.hpp"
#include "PacketOperatorSurcharge.hpp"
#include <SFML/Network.hpp>
#include <iostream>

namespace Network {
class Server {
public:
    Server() = default;
    ~Server();

    void createConnection();

    //      MAIN THREAD -> CREATION OF ROOM + SENDING ROOM LIST
    int createRoom(int playerNb);
    void connectClients();
    void disconnectClient(sf::TcpSocket *, size_t);
    void sendTcpPacket(std::pair<std::pair<sf::IpAddress, unsigned short>, sf::Packet>);
    std::pair<std::pair<sf::IpAddress, unsigned short>, std::pair<Network::Networking, sf::Packet>> receivePacket(sf::TcpSocket *, size_t);
    std::pair<std::pair<sf::IpAddress, unsigned short>, std::pair<Network::Networking, sf::Packet>> retrieveTcpPacket();
    void sendError(std::pair<sf::IpAddress, unsigned short>, std::string errorMsg);

    std::deque<std::pair<sf::IpAddress, unsigned short>> getClientPair() const;
private:
    sf::SocketSelector _selector;
    sf::TcpListener _listener;
    std::deque<sf::TcpSocket *> _clientArray;
    std::deque<std::pair<sf::IpAddress, unsigned short>> _clientPair;

    sf::IpAddress _ip;
    unsigned short _port;
    bool _isTcpUp;
};
}

#endif