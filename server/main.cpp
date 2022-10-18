/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** main
*/

#include <iostream>
#include "Server.hpp"
#include "../Network/NetworkServer.hpp"

int onlyDigit(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] < '0' || str[i] > '9')
            return (1);
    return (0);
}

int main()
{
    Server::Server serv;
    serv.serverLoop();
}