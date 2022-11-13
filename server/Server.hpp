#include "../Network/NetworkServer.hpp"
#include "../Ecs/IncludeComponents.hpp"
#include "../Ecs/IncludeSystem.hpp"
#include "../Ecs/IncludeCpp.hpp"
#include "../Network/NetworkServer.hpp"
#include "../Graphics/Events.hpp"
#include "../Ecs/Manager.hpp"
#include <memory>
#include <SFML/System.hpp>
#include <deque>
#include <list>
#include "surchargeDeque.hpp"
#include "GameInstance/GameServer.hpp"

#define MAX_ENEMIES 15

namespace Server {
class Server {
public:
    Server();
    ~Server() = default;

    void serverLoop();

private:
    void loopPackets();
    void connectClients();
    void checkReady();
    void empacketRoomAskingList(std::pair<sf::IpAddress, unsigned short> client);
    void checkGameThreads();

    bool _up;
    Network::Server _network;
    std::map<int, int> _players;
    std::deque<int> _roomsID;
    std::shared_ptr<Clock> _clock;
    std::deque<std::pair<std::pair<sf::IpAddress, unsigned short>, sf::Packet>> _sendingPackets;
    std::deque<std::pair<std::pair<sf::IpAddress, unsigned short>, std::pair<Network::Networking, sf::Packet>>> _retrievedPackets;
    std::deque<std::shared_ptr<sf::Thread>> _gameServers;
    std::map<int, std::deque<std::pair<sf::IpAddress, unsigned short>>> _clients;   // deque of clients (pair with ip address and port used) sorted by room id

    std::map<size_t, std::shared_ptr<GameServer>> _rooms;
};
}