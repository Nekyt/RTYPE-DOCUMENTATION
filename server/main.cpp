/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** main
*/

#include <iostream>
#include "../Network/NetworkServer.hpp"

int main(int ac, char **av)
{
    NetworkServer set;
    if (ac == 1)
        set.loop(4);
    if (ac == 2)
        set.loop(atoi(av[1]));
    return (0);
}