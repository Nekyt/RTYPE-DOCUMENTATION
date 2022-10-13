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

int onlyDigit(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] < '0' || str[i] > '9')
            return (1);
    return (0);
}

int main(int ac, char **av)
{
    NetworkClient set;

    if (onlyDigit(av[2]) == 1)
        return (84);
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