/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** GameServer
*/

#ifndef GAMESERVER_HPP_
#define GAMESERVER_HPP_

#include "../../Ecs/Manager.hpp"
#include <map>

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
    std::shared_ptr<InitSfml> _graphical; // faut le set
};

#endif /* !GAMESERVER_HPP_ */
