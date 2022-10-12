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

void NetworkClient::engage()
{
    _co = -1;
    if (_udp.bind(sf::Socket::AnyPort) != sf::Socket::Done) {
        printf("fail\n");
        exit (84);
    }
    _selector.add(_udp);
    printf("lisening on port %d\n", _udp.getLocalPort());
    _packet << 0;
    if (_udp.send(_packet, _ip, _port) != sf::Socket::Done) {
        printf("fail send\n");
        exit (84);
    }
    _packet.clear();
    if (_selector.wait(sf::seconds(10))) {
       if (_udp.receive(_packet, _ip, _port) != sf::Socket::Done) {
            printf("fail receive\n");
            exit (84);
        }
        std::cout << "Received from " << _ip << " on port " << _port << std::endl;
        _packet >> _co;
    } else {
        exit (84);
    }
    loop();
}

void NetworkClient::loop()
{
    while (_co == 0) {
        if (_udp.receive(_packet, _ip, _port) != sf::Socket::Done) {
            printf("fail receive\n");
            exit (84);
        }
        std::cout << "Received from " << _ip << " on port " << _port << std::endl;
        _packet >> _co;
    }
    if (_co == -1)
        exit (84);
    std::cout << "test sucess" << std::endl;
}

