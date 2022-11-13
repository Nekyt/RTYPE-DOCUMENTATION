/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** GameServer
*/

#ifndef GAMESERVER_HPP_
#define GAMESERVER_HPP_

#include <deque>
#include "../../Ecs/Manager.hpp"
#include <SFML/System.hpp>
#include "../../Network/NetworkRoom.hpp"

class GameServer {
public:
    GameServer(int players, int roomId);
    ~GameServer() = default;
    void initGameServer();
    void gameLoop();
    bool getEndGame();
    std::pair<sf::IpAddress, unsigned int> getUdpAddress() const;
    std::pair<int, int> getRoomAskingList() const;
    int addPlayer(std::pair<sf::IpAddress, unsigned int> player);
    void playerIsReady(int playerId);
    void playerIsNotReadyAnymore(int playerId);
    bool playerDisconnect(int player);

private:
    void updateAll();
    void gameUpdate();
    void getPlayersMove();
    void setManager();
    ECS::Entity buildPlayer(int playerNb);
    void buildAllPlayers();
    ECS::Entity buildEnnemy();
    void buildAllEnnemies(int maxEnn);
    void checkForEntityDeath();
    void retrievingPackets();
    void waitForFilledRoom();
    void waitForClientsToBeReady();


/*################### NETWORK VARIABLES ###################*/

    Network::Room _network;
    std::pair<sf::IpAddress, unsigned short> _UdpAddress;
    std::shared_ptr<Clock> _networkClock;
    std::map<size_t, std::pair<sf::IpAddress, unsigned int>> _players;
    std::deque<std::pair<std::pair<sf::IpAddress, unsigned short>, sf::Packet>> _sendingPackets;
    std::map<std::pair<sf::IpAddress, unsigned short>, std::deque<std::pair<Network::Networking, sf::Packet>>> _retrievedPackets;

/*#########################################################*/

/*################ GAME CONTROL VARIABLES  ################*/

    std::deque<ECS::Entity> _entities;
    std::shared_ptr<Manager> _manager;
    std::shared_ptr<Clock> _gameClock;
    std::deque<size_t> _playerIds;
    std::deque<bool> _playersReady;
    std::pair<int, int> _roomAskingList; // array containing pairs of rooms's nb of places and nb of people in it
    int _roomId;
    bool _inGame;
    bool _endGame;

/*#########################################################*/
};


#endif /* !GAMESERVER_HPP_ */
