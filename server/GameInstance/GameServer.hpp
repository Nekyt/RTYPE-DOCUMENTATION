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
        void handleNewEnemy(int nbrPlayer);
        void AddNewCommands(int nbrPlayer, Button button);
        void createAllPlayer(int maxPlayers);
        void createAllEnemy(int maxEnemy);

        std::map<int, ECS::Entity> getPlayerList() const;
        std::map<int, ECS::Entity> getEnemyList() const;

        void updateAll();

    protected:
    private:
        Manager _manager;
        std::map<int, ECS::Entity> _mapPlayers;
        std::map<int, ECS::Entity> _mapEnemys;
};

#endif /* !GAMESERVER_HPP_ */
