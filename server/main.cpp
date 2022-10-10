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

    if (socket.bind(sf::Socket::AnyPort) != sf::Socket::Done) {
        printf("fail\n");
        return (84);
    }
    printf("lisening on port %d\n", socket.getLocalPort());
    return (0);
}