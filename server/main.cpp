/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** main
*/

#include <iostream>
#include <SFML/Network.hpp>

int main()
{
    sf::UdpSocket socket;
    sf::IpAddress sender;
    unsigned short port;
    sf::Packet packet;
    int id = 0;
    int co = 1;
    std::vector<std::pair<sf::IpAddress, unsigned short>> clients_co;

    if (socket.bind(sf::Socket::AnyPort) != sf::Socket::Done) {
        printf("fail\n");
        return (84);
    }
    printf("lisening on port %d\n", socket.getLocalPort());
    while (id != 4) {
        if (socket.receive(packet, sender, port) != sf::Socket::Done) {
            printf("fail receive\n");
            exit (84);
        }
        std::cout << "Received from " << sender << " on port " << port << std::endl;
        clients_co.push_back(std::make_pair(sender, port));
        id++;
        std::cout << "connextion register" << std::endl;
    }
    for(int i = 0; i < clients_co.size(); i++) {
        std::cout << "inform client on " << clients_co[i].first << " " << clients_co[i].second << " stop the connection" << std::endl;
        packet << co << id;
        id--;
        if (socket.send(packet, clients_co[i].first, clients_co[i].second) != sf::Socket::Done) {
            printf("fail send\n");
            exit (84);
        }
    }
    return (0);
}