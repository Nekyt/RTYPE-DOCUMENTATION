/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** main
*/

#include <iostream>
#include "../Network/NetworkServer.hpp"

int onlyDigit(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] < '0' || str[i] > '9')
            return (1);
    return (0);
}

int main(int ac, char **av)
{
    NetworkServer set;
    if (ac == 1)
        set.loop(4);
    if (ac == 2) {
        if (onlyDigit(av[1]) == 0) {
            set.loop(atoi(av[1]));
        } else {
            return (84);
        }
    }
    return (0);
}