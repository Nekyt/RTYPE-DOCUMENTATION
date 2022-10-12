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

//int program()
//{
//    GameClient client;
//
//    client.gameLoop();
//    return 0;
//}

int main(int ac, char **av)
{
    NetworkClient set;
    set.setIp(av[1]);
    set.setPort(atoi(av[2]));
    set.engage();
    return (0);
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