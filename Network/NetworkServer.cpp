/*
** EPITECH PROJECT, 2022
** B-CPP-500-STG-5-1-rtype-romanie.de-meyer
** File description:
** NetworkServer
*/

#include "NetworkServer.hpp"

void NetworkServer::loop()
{
    int id = 0;
    int co = 1;

    if (_udp.bind(sf::Socket::AnyPort) != sf::Socket::Done) {
        printf("fail\n");
        exit (84);
    }
    std::cout << "lisening on port " << _udp.getLocalPort() << " ip " << sf::IpAddress::getLocalAddress() << std::endl;
    while (id != 4) {
        if (_udp.receive(_packet, _ip, _port) != sf::Socket::Done) {
            printf("fail receive\n");
            exit (84);
        }
        std::cout << "Received " << _packet << " from " << _ip << " on port " << _port << std::endl;
        _clients.push_back(std::make_pair(_ip, _port));
        id++;
        std::cout << "connextion register" << std::endl;
    }
    for (int i = 0; i < _clients.size(); i++) {
        std::cout << "inform client on " << _clients[i].first << " " << _clients[i].second << " stop the connection" << std::endl;
         _packet.clear();
        _packet << co;
        id--;
        std::cout << _packet << std::endl;
        if (_udp.send(_packet, _clients[i].first, _clients[i].second) != sf::Socket::Done) {
            printf("fail send\n");
            exit (84);
        }
    }
}

