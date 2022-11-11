/*
** EPITECH PROJECT, 2022
** B-CPP-500-STG-5-1-rtype-romanie.de-meyer
** File description:
** NetworkClient
*/

#ifndef NETWORKCLIENT_HPP_
#define NETWORKCLIENT_HPP_

#include <iostream>
#include <list>
#include <SFML/Network.hpp>
#include "../Graphics/Events.hpp"

namespace Network {
class Client {
    public:
        Client(const char* ip, unsigned short port);
        ~Client() = default;

        void roomCreation(int players);
        std::deque<int> roomAskingList();
        int joinRoom(std::deque<int> rooms);
        sf::Packet retrievePacket();
        int getRoomId() const;
        int sendPacket(sf::Packet packet);


    protected:
    private:
        std::deque<int> packetTodequeInt(sf::Packet packet, int size);

        sf::UdpSocket _udp;
        sf::SocketSelector _selector;
        sf::IpAddress _ip;
        int _roomId;
        unsigned short _port;
};
};

#endif /* !NETWORKCLIENT_HPP_ */
