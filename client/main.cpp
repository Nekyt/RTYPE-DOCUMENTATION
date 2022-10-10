/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** main
*/

//#include "./GameClient.hpp"
#include <SFML/Network.hpp>
#include <iostream>

//int program()
//{
//    GameClient client;
//
//    client.gameLoop();
//    return 0;
//}

int main(int ac, char **av)
{
    sf::UdpSocket socket;
    sf::IpAddress recipient = "127.0.0.1";
    unsigned short port = atoi(av[1]);
    sf::Packet packet;
    int x = -1;
    int co = 0;

    if (socket.bind(sf::Socket::AnyPort) != sf::Socket::Done) {
        printf("fail\n");
        return (84);
    }
    printf("lisening on port %d\n", socket.getLocalPort());
    packet << x;
        if (socket.send(packet, recipient, port) != sf::Socket::Done) {
            printf("fail send\n");
            exit (84);
        }
    while (co == 0) {
         if (socket.receive(packet, recipient, port) != sf::Socket::Done) {
            printf("fail receive\n");
            exit (84);
        }
        std::cout << "Received from " << recipient << " on port " << port << std::endl;
        packet >> co;
    }
    std::cout << "test sucess" << std::endl;
    //try {
    //    return program();
    //} catch(std::exception& e) {
    //    std::cerr << "Error (stdexcept): " << e.what() << '\n';
    //    return 84;
    //} catch (...) {
    //    std::cerr << "Error: Unknown exception !!!!!!\n";
    //    return 84;
    //}
}