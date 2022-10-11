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

    protected:
    private:
        sf::UdpSocket _udp;
        sf::IpAddress _ip;
        unsigned short _port;
        sf::Packet _packet;
};

#endif /* !NETWORKCLIENT_HPP_ */
