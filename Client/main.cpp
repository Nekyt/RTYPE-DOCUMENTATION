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
#include <SFML/System.hpp>
#include "GameClient.hpp"

//int program()
//{
//    GameClient client;
//
//    client.gameLoop();
//    return 0;
//}

int main(int ac, char **av)
{
    if  (ac == 3) {
        std::cout << "ARGS : " << av[1] << " " << av[2] << std::endl;
        GameClient client(av[1], atoi(av[2]));

        client.gameLoop();
    }
}