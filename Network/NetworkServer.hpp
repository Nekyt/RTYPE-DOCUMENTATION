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

class NetworkServer {
    public:
        NetworkServer() = default;
        ~NetworkServer() = default;
        void loop(void);
        void engage(int);
        void waitClient(int);
    protected:
    private:
        std::vector<std::pair<sf::IpAddress, unsigned short>> _clients;
        sf::UdpSocket _udp;
        sf::IpAddress _ip;
        unsigned short _port;
        sf::Packet _packet;
};

#endif /* !NETWORKSERVER_HPP_ */
