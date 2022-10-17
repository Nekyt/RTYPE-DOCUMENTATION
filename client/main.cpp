/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** main
*/

//#include "./GameClient.hpp"
#include <SFML/Network.hpp>
#include "../Network/NetworkClient.hpp"
#include <iostream>
#include "../Network/Enum.hpp"

//int program()
//{
//    GameClient client;
//
//    client.gameLoop();
//    return 0;
//}

int onlyDigit(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] < '0' || str[i] > '9')
            return (1);
    return (0);
}

int main(int ac, char **av)
{
    std::vector<int> tab;
    sf::Packet packet;
    int type;
    int playerId;

    if (ac < 3 || onlyDigit(av[2]) == 1)
        return (84);

    Network::Client set(av[1], atoi(av[2]));
    set.roomCreation(3);
    tab = set.roomAskingList();
    std::cout << "Rooms List : " << std::endl;
    for (size_t i = 0; i < tab.size(); ++i)
        std::cout << tab[i] << std::endl;
    set.joinRoom(tab);
    packet = set.retrievePacket();
    packet >> type;
    if (type == Network::Networking::ERROR) {
        exit (84);
    }
    packet >> playerId;
    std::cout << "Player ID : " << playerId << std::endl;
    packet.clear();
    packet = set.retrievePacket();
    packet.clear();
    set.sendReady();

}