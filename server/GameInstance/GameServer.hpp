/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** GameServer
*/

#ifndef GAMESERVER_HPP_
#define GAMESERVER_HPP_

#include <map>
#include "../../Ecs/Manager.hpp"

class GameServer {
    public:
        GameServer();
        ~GameServer() = default;

        void handleNewClient(int nbrPlayer);
        void handleNewEnenmy(int nbrPlayer);
        void AddNewCommands(int nbrPlayer, Button button);
        void updateAll();

    protected:
    private:
        Manager _manager;
        std::map<int, ECS::Entity> _mapPlayers;
};

#endif /* !GAMESERVER_HPP_ */
