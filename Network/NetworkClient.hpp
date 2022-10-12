/*
** EPITECH PROJECT, 2022
** B-CPP-500-STG-5-1-rtype-romanie.de-meyer
** File description:
** NetworkClient
*/

#ifndef NETWORKCLIENT_HPP_
#define NETWORKCLIENT_HPP_

#include <iostream>
#include <SFML/Network.hpp>

class NetworkClient {
    public:
        NetworkClient() = default;
        ~NetworkClient() = default;
        void setIp(const char *);
        void setPort(unsigned short);
        void loop();
        void engage();

    protected:
    private:
        sf::UdpSocket _udp;
        sf::SocketSelector _selector;
        sf::IpAddress _ip;
        unsigned short _port;
        sf::Packet _packet;
        int _co;
};

#endif /* !NETWORKCLIENT_HPP_ */
