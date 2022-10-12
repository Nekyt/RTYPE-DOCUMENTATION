/*
** EPITECH PROJECT, 2022
** B-CPP-500-STG-5-1-rtype-romanie.de-meyer
** File description:
** NetworkServer
*/

#include "NetworkServer.hpp"

void NetworkServer::engage(int n)
{
    if (n < 2 || n > 4)
        exit (84);
    if (_udp.bind(sf::Socket::AnyPort) != sf::Socket::Done) {
        printf("fail\n");
        exit (84);
    }
    std::cout << "lisening on port " << _udp.getLocalPort() << " ip " << sf::IpAddress::getLocalAddress() << std::endl;
    waitClient(n);
}

void NetworkServer::waitClient(int n)
{
    int id = 0;

    while (id != n) {
        if (_udp.receive(_packet, _ip, _port) != sf::Socket::Done) {
            printf("fail receive\n");
            exit (84);
        }
        std::cout << "Received " << _packet << " from " << _ip << " on port " << _port << std::endl;
        _clients.push_back(std::make_pair(_ip, _port));
        id++;
        std::cout << "connextion register" << std::endl;
        _packet.clear();
        _packet << 0 << id;
         if (_udp.send(_packet, _ip, _port) != sf::Socket::Done) {
            printf("fail send\n");
            exit (84);
        }
        _packet.clear();
    }
    loop();
}

void NetworkServer::loop()
{
    int co = 1;

    for (int i = 0; i < _clients.size(); i++) {
        std::cout << "inform client on " << _clients[i].first << " " << _clients[i].second << " stop the connection" << std::endl;
        _packet.clear();
        _packet << co;
        if (_udp.send(_packet, _clients[i].first, _clients[i].second) != sf::Socket::Done) {
            printf("fail send\n");
            exit (84);
        }
    }
}

