/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** main
*/

#include "./GameClient.hpp"

int program()
{
    GameClient client;

    client.gameLoop();
    return 0;
}

int main()
{
    try {
        return program();
    } catch(std::exception& e) {
        std::cerr << "Error (stdexcept): " << e.what() << '\n';
        return 84;
    } catch (...) {
        std::cerr << "Error: Unknown exception !!!!!!\n";
        return 84;
    }
}