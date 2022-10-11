/*
** EPITECH PROJECT, 2022
** B-CPP-500-STG-5-1-rtype-romanie.de-meyer
** File description:
** NetworkClient
*/

#include "NetworkClient.hpp"

void NetworkClient::setIp(const char *ip)
{
    _ip = ip;
}

void NetworkClient::setPort(const unsigned short port)
{
    _port = port;
}

void NetworkClient::loop()
{
    int x = 56;
    int co = 0;

    if (_udp.bind(sf::Socket::AnyPort) != sf::Socket::Done) {
        printf("fail\n");
        exit (84);
    }
    printf("lisening on port %d\n", _udp.getLocalPort());
    _packet << x;
    if (_udp.send(_packet, _ip, _port) != sf::Socket::Done) {
        printf("fail send\n");
        exit (84);
    }
    _packet.clear();
    while (co == 0) {
        if (_udp.receive(_packet, _ip, _port) != sf::Socket::Done) {
            printf("fail receive\n");
            exit (84);
        }
        std::cout << "Received from " << _ip << " on port " << _port << std::endl;
        std::cout << co << std::endl;
        _packet >> co;
        std::cout << co << std::endl;
    }
    if (co == -1)
        exit (84);
    std::cout << "test sucess" << std::endl;
}

